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

typedef void *LPDIRECTSOUND;
typedef void *LPDIRECTSOUNDBUFFER;

static inline LONG DirectSoundCreate(void *guid, LPDIRECTSOUND *ds, void *unk) {
    (void)guid; (void)unk;
    if (ds) *ds = NULL;
    return DS_OK;
}

#ifdef __cplusplus
}
#endif

#endif // _DSOUND_H_STUB
