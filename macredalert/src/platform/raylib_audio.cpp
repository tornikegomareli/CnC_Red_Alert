/*
 * raylib_audio.cpp — Audio bridge for Red Alert macOS port
 *
 * Implements File_Stream_Sample_Vol using Raylib's audio system.
 * Decodes Westwood's AUD format (IMA ADPCM) and streams via Raylib.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "FUNCTION.H"

#undef Color
#undef BLACK
#undef WHITE
#undef GREEN
#undef RED
#undef YELLOW
#undef BLUE
#undef PURPLE
#undef CYAN
#undef GREY
#undef LTGREY
#undef LTGREEN
#undef LTCYAN
#undef LTBLUE
#undef BROWN
#undef PINK

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmacro-redefined"
#include "raylib.h"
#pragma clang diagnostic pop

extern void ra_log(const char *fmt, ...);

/* IMA ADPCM step table */
static const int ima_step_table[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

static const int ima_index_table[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};

/*
 * Westwood AUD file header (12 bytes)
 */
#pragma pack(push, 1)
struct AUDHeader {
    unsigned short rate;        /* Sample rate */
    unsigned int   uncomp_size; /* Uncompressed data size */
    unsigned int   comp_size;   /* Compressed data size */
    unsigned char  flags;       /* bit 0 = stereo, bit 1 = 16-bit */
    unsigned char  comp_type;   /* 1 = WW compress, 99 = IMA ADPCM */
};

/* AUD chunk header (8 bytes) — data is split into chunks */
struct AUDChunkHeader {
    unsigned short uncomp_size; /* Uncompressed size of this chunk */
    unsigned short comp_size;   /* Compressed size of this chunk */
    unsigned int   id;          /* Should be 0x0000DEAF */
};
#pragma pack(pop)

/* State for streaming audio */
static Music g_current_music = {0};
static bool g_music_playing = false;
static bool g_audio_initialized = false;

/*
 * Decode IMA ADPCM data to 16-bit PCM
 */
static int decode_ima_adpcm(const unsigned char *src, int src_len,
                             short *dst, int dst_max_samples) {
    int sample = 0;
    int step_index = 0;
    int out_count = 0;

    for (int i = 0; i < src_len && out_count < dst_max_samples; i++) {
        unsigned char byte = src[i];

        /* Process low nibble then high nibble */
        for (int nibble_idx = 0; nibble_idx < 2 && out_count < dst_max_samples; nibble_idx++) {
            int nibble = (nibble_idx == 0) ? (byte & 0x0F) : ((byte >> 4) & 0x0F);

            int step = ima_step_table[step_index];
            int diff = step >> 3;
            if (nibble & 1) diff += step >> 2;
            if (nibble & 2) diff += step >> 1;
            if (nibble & 4) diff += step;
            if (nibble & 8) diff = -diff;

            sample += diff;
            if (sample > 32767) sample = 32767;
            if (sample < -32768) sample = -32768;

            dst[out_count++] = (short)sample;

            step_index += ima_index_table[nibble];
            if (step_index < 0) step_index = 0;
            if (step_index > 88) step_index = 88;
        }
    }
    return out_count;
}

/*
 * File_Stream_Sample_Vol — Stream an AUD file through Raylib audio.
 * Called by ThemeClass::Play_Song to play music.
 */
int File_Stream_Sample_Vol(char const *name, int volume, int loop) {
    ra_log("[AUDIO] File_Stream_Sample_Vol('%s', vol=%d, loop=%d)\n",
           name ? name : "NULL", volume, loop);

    if (!name) return -1;

    /* Initialize Raylib audio if needed */
    if (!g_audio_initialized) {
        InitAudioDevice();
        g_audio_initialized = true;
        ra_log("[AUDIO] Audio device initialized\n");
    }

    /* Stop any currently playing music */
    if (g_music_playing) {
        StopMusicStream(g_current_music);
        UnloadMusicStream(g_current_music);
        g_music_playing = false;
    }

    /* Open the AUD file via the game's file system */
    CCFileClass file(name);
    if (!file.Is_Available()) {
        ra_log("[AUDIO] File not available: %s\n", name);
        return -1;
    }

    int file_size = file.Size();
    ra_log("[AUDIO] File size: %d\n", file_size);

    file.Open(READ);
    unsigned char *data = new unsigned char[file_size];
    file.Read(data, file_size);
    file.Close();

    /* Parse AUD header */
    if (file_size < 12) { delete[] data; return -1; }
    AUDHeader *hdr = (AUDHeader *)data;

    ra_log("[AUDIO] AUD: rate=%d, uncomp=%d, comp=%d, flags=0x%02X, type=%d\n",
           hdr->rate, hdr->uncomp_size, hdr->comp_size, hdr->flags, hdr->comp_type);

    if (hdr->comp_type != 99) {
        ra_log("[AUDIO] Unsupported compression type %d\n", hdr->comp_type);
        delete[] data;
        return -1;
    }

    /* Decode all chunks */
    int total_samples = hdr->uncomp_size / 2; /* 16-bit samples */
    short *pcm = new short[total_samples + 4096];
    int pcm_offset = 0;

    unsigned char *ptr = data + 12; /* Skip AUD header */
    unsigned char *end = data + file_size;

    while (ptr + 8 <= end && pcm_offset < total_samples) {
        AUDChunkHeader *chunk = (AUDChunkHeader *)ptr;

        /* Validate chunk */
        if ((chunk->id & 0x0000FFFF) != 0xDEAF) break;

        ptr += 8; /* Skip chunk header */
        if (ptr + chunk->comp_size > end) break;

        int decoded = decode_ima_adpcm(ptr, chunk->comp_size,
                                        pcm + pcm_offset,
                                        total_samples - pcm_offset);
        pcm_offset += decoded;
        ptr += chunk->comp_size;
    }

    ra_log("[AUDIO] Decoded %d samples (%.1f seconds)\n",
           pcm_offset, (float)pcm_offset / hdr->rate);

    if (pcm_offset == 0) {
        delete[] pcm;
        delete[] data;
        return -1;
    }

    /* Save as WAV in temp file for Raylib to load */
    char wav_path[256];
    snprintf(wav_path, sizeof(wav_path), "/tmp/ra_theme_%s.wav", name);

    /* Write WAV file */
    FILE *wav = fopen(wav_path, "wb");
    if (wav) {
        int data_size = pcm_offset * 2; /* 16-bit = 2 bytes per sample */
        int channels = 1;
        int bits = 16;

        /* RIFF header */
        fwrite("RIFF", 1, 4, wav);
        int riff_size = 36 + data_size;
        fwrite(&riff_size, 4, 1, wav);
        fwrite("WAVE", 1, 4, wav);

        /* fmt chunk */
        fwrite("fmt ", 1, 4, wav);
        int fmt_size = 16;
        fwrite(&fmt_size, 4, 1, wav);
        short audio_fmt = 1; /* PCM */
        fwrite(&audio_fmt, 2, 1, wav);
        short num_channels = channels;
        fwrite(&num_channels, 2, 1, wav);
        int sample_rate = hdr->rate;
        fwrite(&sample_rate, 4, 1, wav);
        int byte_rate = sample_rate * channels * bits / 8;
        fwrite(&byte_rate, 4, 1, wav);
        short block_align = channels * bits / 8;
        fwrite(&block_align, 2, 1, wav);
        short bits_per_sample = bits;
        fwrite(&bits_per_sample, 2, 1, wav);

        /* data chunk */
        fwrite("data", 1, 4, wav);
        fwrite(&data_size, 4, 1, wav);
        fwrite(pcm, 2, pcm_offset, wav);

        fclose(wav);
        ra_log("[AUDIO] Saved WAV: %s (%d bytes)\n", wav_path, 44 + data_size);

        /* Load and play via Raylib */
        g_current_music = LoadMusicStream(wav_path);
        if (g_current_music.frameCount > 0) {
            g_current_music.looping = (loop != 0);
            SetMusicVolume(g_current_music, volume / 255.0f);
            PlayMusicStream(g_current_music);
            g_music_playing = true;
            ra_log("[AUDIO] Playing music! Duration: %.1fs\n",
                   GetMusicTimeLength(g_current_music));
        } else {
            ra_log("[AUDIO] Failed to load WAV\n");
        }
    }

    delete[] pcm;
    delete[] data;

    return g_music_playing ? 1 : -1;
}

/*
 * Update music stream — must be called regularly from the render loop
 */
extern "C" void Raylib_Update_Audio(void) {
    if (g_music_playing) {
        UpdateMusicStream(g_current_music);
    }
}
