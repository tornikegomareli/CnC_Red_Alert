/* Stub ddraw.h — DirectDraw type definitions for compilation */
#ifndef _DDRAW_H_STUB
#define _DDRAW_H_STUB

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

// DirectDraw return codes
#define DD_OK                           0
#define DDERR_SURFACELOST               0x887601C2L
#define DDERR_WASSTILLDRAWING           0x8876021CL
#define DDERR_GENERIC                   0x80004005L
#define DDERR_INVALIDPARAMS             0x80070057L
#define DDERR_UNSUPPORTED               0x80004001L

// DirectDraw cooperative level flags
#define DDSCL_FULLSCREEN                0x00000001
#define DDSCL_ALLOWREBOOT               0x00000002
#define DDSCL_NOWINDOWCHANGES           0x00000004
#define DDSCL_NORMAL                    0x00000008
#define DDSCL_EXCLUSIVE                 0x00000010
#define DDSCL_ALLOWMODEX                0x00000040

// Surface description flags
#define DDSD_CAPS                       0x00000001
#define DDSD_HEIGHT                     0x00000002
#define DDSD_WIDTH                      0x00000004
#define DDSD_PITCH                      0x00000008
#define DDSD_PIXELFORMAT                0x00001000
#define DDSD_BACKBUFFERCOUNT            0x00000020

// Surface caps
#define DDSCAPS_PRIMARYSURFACE          0x00000200
#define DDSCAPS_OFFSCREENPLAIN          0x00000040
#define DDSCAPS_SYSTEMMEMORY            0x00000800
#define DDSCAPS_VIDEOMEMORY             0x00004000
#define DDSCAPS_MODEX                   0x00200000
#define DDSCAPS_FLIP                    0x00000010
#define DDSCAPS_COMPLEX                 0x00000008

// Blt flags
#define DDBLT_KEYSRC                    0x00008000
#define DDBLT_WAIT                      0x01000000
#define DDBLT_ASYNC                     0x00000200
#define DDBLT_COLORFILL                 0x00000400

// Lock flags
#define DDLOCK_WAIT                     0x00000001
#define DDLOCK_SURFACEMEMORYPTR          0x00000000

// Color key flags
#define DDCKEY_SRCBLT                   0x00000008

// Palette caps
#define DDPCAPS_8BIT                    0x00000004
#define DDPCAPS_ALLOW256                0x00000040

// Structures
typedef struct _DDSCAPS {
    DWORD dwCaps;
} DDSCAPS;

typedef struct _DDCOLORKEY {
    DWORD dwColorSpaceLowValue;
    DWORD dwColorSpaceHighValue;
} DDCOLORKEY;

typedef struct _DDPIXELFORMAT {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwFourCC;
    DWORD dwRGBBitCount;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;
    DWORD dwRGBAlphaBitMask;
} DDPIXELFORMAT;

typedef struct _DDSURFACEDESC {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwHeight;
    DWORD dwWidth;
    union {
        LONG lPitch;
        DWORD dwLinearSize;
    };
    DWORD dwBackBufferCount;
    DWORD dwRefreshRate;
    DWORD dwAlphaBitDepth;
    DWORD dwReserved;
    LPVOID lpSurface;
    DDCOLORKEY ddckCKDestOverlay;
    DDCOLORKEY ddckCKDestBlt;
    DDCOLORKEY ddckCKSrcOverlay;
    DDCOLORKEY ddckCKSrcBlt;
    DDPIXELFORMAT ddpfPixelFormat;
    DDSCAPS ddsCaps;
} DDSURFACEDESC, *LPDDSURFACEDESC;

typedef struct _DDBLTFX {
    DWORD dwSize;
    DWORD dwDDFX;
    DWORD dwFillColor;
} DDBLTFX, *LPDDBLTFX;

typedef struct _DDCAPS {
    DWORD dwSize;
    DWORD dwCaps;
    DWORD dwVidMemTotal;
    DWORD dwVidMemFree;
} DDCAPS, *LPDDCAPS;

// Blt status flags
#define DDGBS_CANBLT                    0x00000001
#define DDGBS_ISBLTDONE                 0x00000002

// Interface stubs — void pointers since we don't use COM
typedef void *LPDIRECTDRAW;
typedef void *LPDIRECTDRAW2;
typedef void *LPDIRECTDRAWSURFACE;
typedef void *LPDIRECTDRAWSURFACE2;
typedef void *LPDIRECTDRAWPALETTE;
typedef void *LPDIRECTDRAWCLIPPER;

// DirectDraw creation function
static inline LONG DirectDrawCreate(void *guid, LPDIRECTDRAW *dd, void *unk) {
    (void)guid; (void)unk;
    if (dd) *dd = NULL;
    return DD_OK;
}

#ifdef __cplusplus
}
#endif

#endif // _DDRAW_H_STUB
