/* Stub dsound.h — DirectSound type definitions */
#ifndef _DSOUND_H_STUB
#define _DSOUND_H_STUB

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DS_OK                       0
#define DSERR_BUFFERLOST            0x88780096L
#define DSBPLAY_LOOPING             0x00000001

#define DSBCAPS_PRIMARYBUFFER       0x00000001
#define DSBCAPS_STATIC              0x00000002
#define DSBCAPS_CTRLPAN             0x00000040
#define DSBCAPS_CTRLVOLUME          0x00000080
#define DSBCAPS_CTRLFREQUENCY       0x00000020
#define DSBCAPS_GETCURRENTPOSITION2 0x00010000

#define DSSCL_NORMAL                1
#define DSSCL_PRIORITY              2
#define DSSCL_EXCLUSIVE             3

#define WAVE_FORMAT_PCM             1

#ifndef _WAVEFORMATEX_DEFINED
#define _WAVEFORMATEX_DEFINED
typedef struct tWAVEFORMATEX {
    WORD  wFormatTag;
    WORD  nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD  nBlockAlign;
    WORD  wBitsPerSample;
    WORD  cbSize;
} WAVEFORMATEX, *LPWAVEFORMATEX;
#endif

typedef struct _DSBUFFERDESC {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwBufferBytes;
    DWORD dwReserved;
    LPWAVEFORMATEX lpwfxFormat;
} DSBUFFERDESC, *LPDSBUFFERDESC;

typedef struct _DSBCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwBufferBytes;
    DWORD dwUnlockTransferRate;
    DWORD dwPlayCpuOverhead;
} DSBCAPS, *LPDSBCAPS;

#ifdef __cplusplus

struct IDirectSoundBuffer {
    LONG Lock(DWORD off, DWORD bytes, LPVOID *ptr1, LPDWORD sz1, LPVOID *ptr2, LPDWORD sz2, DWORD flags) {
        (void)off; (void)bytes; (void)ptr1; (void)sz1; (void)ptr2; (void)sz2; (void)flags; return DS_OK;
    }
    LONG Unlock(LPVOID ptr1, DWORD sz1, LPVOID ptr2, DWORD sz2) {
        (void)ptr1; (void)sz1; (void)ptr2; (void)sz2; return DS_OK;
    }
    LONG Play(DWORD res1, DWORD res2, DWORD flags) { (void)res1; (void)res2; (void)flags; return DS_OK; }
    LONG Stop() { return DS_OK; }
    LONG SetVolume(LONG vol) { (void)vol; return DS_OK; }
    LONG SetPan(LONG pan) { (void)pan; return DS_OK; }
    LONG SetFrequency(DWORD freq) { (void)freq; return DS_OK; }
    LONG GetStatus(LPDWORD status) { if (status) *status = 0; return DS_OK; }
    LONG GetCurrentPosition(LPDWORD play, LPDWORD write) { (void)play; (void)write; return DS_OK; }
    LONG SetCurrentPosition(DWORD pos) { (void)pos; return DS_OK; }
    LONG Restore() { return DS_OK; }
    LONG GetCaps(LPDSBCAPS caps) { (void)caps; return DS_OK; }
    LONG SetFormat(LPWAVEFORMATEX fmt) { (void)fmt; return DS_OK; }
    LONG Release() { return 0; }
};

struct IDirectSound {
    LONG SetCooperativeLevel(HWND hwnd, DWORD level) { (void)hwnd; (void)level; return DS_OK; }
    LONG CreateSoundBuffer(LPDSBUFFERDESC desc, IDirectSoundBuffer **buf, void *unk) {
        (void)desc; (void)unk;
        static IDirectSoundBuffer dummy;
        if (buf) *buf = &dummy;
        return DS_OK;
    }
    LONG GetCaps(void *caps) { (void)caps; return DS_OK; }
    LONG Release() { return 0; }
};

typedef IDirectSound *LPDIRECTSOUND;
typedef IDirectSoundBuffer *LPDIRECTSOUNDBUFFER;

#else
typedef void *LPDIRECTSOUND;
typedef void *LPDIRECTSOUNDBUFFER;
#endif

static inline LONG DirectSoundCreate(void *guid, LPDIRECTSOUND *ds, void *unk) {
    (void)guid; (void)unk;
    if (ds) *ds = NULL;
    return DS_OK;
}

#ifdef __cplusplus
}
#endif

#endif // _DSOUND_H_STUB
