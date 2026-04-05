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

// Wait for vertical blank
#define DDWAITVB_BLOCKBEGIN             0x00000001

// GUID placeholder
typedef struct _GUID { DWORD Data1; } GUID, IID;
#define IID_IDirectDraw2 (*(IID*)0)

#ifdef __cplusplus

// IDirectDrawPalette stub
struct IDirectDrawPalette {
    LONG SetEntries(DWORD flags, DWORD start, DWORD count, LPPALETTEENTRY entries) {
        (void)flags; (void)start; (void)count; (void)entries; return DD_OK;
    }
    LONG Release() { return 0; }
};

// IDirectDrawSurface stub
struct IDirectDrawSurface {
    LONG Lock(LPRECT rect, LPDDSURFACEDESC desc, DWORD flags, HANDLE event) {
        (void)rect; (void)desc; (void)flags; (void)event; return DD_OK;
    }
    LONG Unlock(LPVOID ptr) { (void)ptr; return DD_OK; }
    LONG Release() { return 0; }
    LONG Blt(LPRECT dst, IDirectDrawSurface *src, LPRECT srcrect, DWORD flags, LPDDBLTFX fx) {
        (void)dst; (void)src; (void)srcrect; (void)flags; (void)fx; return DD_OK;
    }
    LONG BltFast(DWORD x, DWORD y, IDirectDrawSurface *src, LPRECT srcrect, DWORD flags) {
        (void)x; (void)y; (void)src; (void)srcrect; (void)flags; return DD_OK;
    }
    LONG GetBltStatus(DWORD flags) { (void)flags; return DD_OK; }
    LONG SetPalette(IDirectDrawPalette *pal) { (void)pal; return DD_OK; }
    LONG SetColorKey(DWORD flags, DDCOLORKEY *key) { (void)flags; (void)key; return DD_OK; }
    LONG Restore() { return DD_OK; }
    LONG GetSurfaceDesc(LPDDSURFACEDESC desc) { (void)desc; return DD_OK; }
    LONG AddAttachedSurface(IDirectDrawSurface *surf) { (void)surf; return DD_OK; }
    LONG Flip(IDirectDrawSurface *surf, DWORD flags) { (void)surf; (void)flags; return DD_OK; }
};

// IDirectDraw stub
struct IDirectDraw {
    LONG SetCooperativeLevel(HWND hwnd, DWORD flags) { (void)hwnd; (void)flags; return DD_OK; }
    LONG SetDisplayMode(DWORD w, DWORD h, DWORD bpp) { (void)w; (void)h; (void)bpp; return DD_OK; }
    LONG CreateSurface(LPDDSURFACEDESC desc, IDirectDrawSurface **surf, void *unk) {
        (void)desc; (void)unk;
        static IDirectDrawSurface dummy;
        if (surf) *surf = &dummy;
        return DD_OK;
    }
    LONG CreatePalette(DWORD flags, LPPALETTEENTRY entries, IDirectDrawPalette **pal, void *unk) {
        (void)flags; (void)entries; (void)unk;
        static IDirectDrawPalette dummy;
        if (pal) *pal = &dummy;
        return DD_OK;
    }
    LONG RestoreDisplayMode() { return DD_OK; }
    LONG Release() { return 0; }
    LONG GetCaps(LPDDCAPS driver, LPDDCAPS emul) { (void)driver; (void)emul; return DD_OK; }
    LONG WaitForVerticalBlank(DWORD flags, HANDLE event) { (void)flags; (void)event; return DD_OK; }
    LONG QueryInterface(IID &iid, LPVOID *obj) { (void)iid; (void)obj; return DD_OK; }
};

// IDirectDraw2 stub
struct IDirectDraw2 {
    LONG GetAvailableVidMem(DDSCAPS *caps, LPDWORD total, LPDWORD free_mem) {
        (void)caps; if (total) *total = 0; if (free_mem) *free_mem = 0; return DD_OK;
    }
    LONG Release() { return 0; }
};

typedef IDirectDraw *LPDIRECTDRAW;
typedef IDirectDraw2 *LPDIRECTDRAW2;
typedef IDirectDrawSurface *LPDIRECTDRAWSURFACE;
typedef IDirectDrawSurface *LPDIRECTDRAWSURFACE2;
typedef IDirectDrawPalette *LPDIRECTDRAWPALETTE;
typedef void *LPDIRECTDRAWCLIPPER;

#else
typedef void *LPDIRECTDRAW;
typedef void *LPDIRECTDRAW2;
typedef void *LPDIRECTDRAWSURFACE;
typedef void *LPDIRECTDRAWSURFACE2;
typedef void *LPDIRECTDRAWPALETTE;
typedef void *LPDIRECTDRAWCLIPPER;
#endif

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
