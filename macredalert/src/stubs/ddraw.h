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
#define DDERR_ALREADYINITIALIZED        0x88760001L
#define DDERR_CANNOTATTACHSURFACE       0x88760002L
#define DDERR_CANNOTDETACHSURFACE       0x88760003L
#define DDERR_CURRENTLYNOTAVAIL         0x88760004L
#define DDERR_EXCEPTION                 0x88760005L
#define DDERR_HEIGHTALIGN               0x88760006L
#define DDERR_INCOMPATIBLEPRIMARY       0x88760007L
#define DDERR_INVALIDCAPS               0x88760008L
#define DDERR_INVALIDCLIPLIST           0x88760009L
#define DDERR_INVALIDMODE               0x8876000AL
#define DDERR_INVALIDOBJECT             0x8876000BL
#define DDERR_INVALIDPIXELFORMAT        0x8876000CL
#define DDERR_INVALIDRECT               0x8876000DL
#define DDERR_LOCKEDSURFACES            0x8876000EL
#define DDERR_NO3D                      0x8876000FL
#define DDERR_NOALPHAHW                 0x88760010L
#define DDERR_NOCLIPLIST                0x88760011L
#define DDERR_NOCOLORCONVHW             0x88760012L
#define DDERR_NOCOOPERATIVELEVELSET     0x88760013L
#define DDERR_NOCOLORKEY                0x88760014L
#define DDERR_NOCOLORKEYHW              0x88760015L
#define DDERR_NODIRECTDRAWSUPPORT       0x88760016L
#define DDERR_NOEXCLUSIVEMODE           0x88760017L
#define DDERR_NOFLIPHW                  0x88760018L
#define DDERR_NOGDI                     0x88760019L
#define DDERR_NOMIRRORHW                0x8876001AL
#define DDERR_NOTFOUND                  0x8876001BL
#define DDERR_NOOVERLAYHW               0x8876001CL
#define DDERR_OVERLAPPINGRECTS          0x8876001DL
#define DDERR_NORASTEROPHW              0x8876001EL
#define DDERR_NOROTATIONHW              0x8876001FL
#define DDERR_NOSTRETCHHW               0x88760020L
#define DDERR_NOT4BITCOLOR              0x88760021L
#define DDERR_NOT4BITCOLORINDEX         0x88760022L
#define DDERR_NOT8BITCOLOR              0x88760023L
#define DDERR_NOTEXTUREHW               0x88760024L
#define DDERR_NOVSYNCHW                 0x88760025L
#define DDERR_NOZBUFFERHW               0x88760026L
#define DDERR_NOZOVERLAYHW              0x88760027L
#define DDERR_OUTOFCAPS                 0x88760028L
#define DDERR_OUTOFMEMORY               0x88760029L
#define DDERR_OUTOFVIDEOMEMORY          0x8876002AL
#define DDERR_OVERLAYCANTCLIP           0x8876002BL
#define DDERR_OVERLAYCOLORKEYONLYONEACTIVE 0x8876002CL
#define DDERR_PALETTEBUSY               0x8876002DL
#define DDERR_COLORKEYNOTSET            0x8876002EL
#define DDERR_SURFACEALREADYATTACHED    0x8876002FL
#define DDERR_SURFACEALREADYDEPENDENT   0x88760030L
#define DDERR_SURFACEBUSY               0x88760031L
#define DDERR_CANTLOCKSURFACE           0x88760032L
#define DDERR_SURFACEISOBSCURED         0x88760033L
#define DDERR_SURFACENOTATTACHED        0x88760034L
#define DDERR_TOOBIGHEIGHT              0x88760035L
#define DDERR_TOOBIGSIZE                0x88760036L
#define DDERR_TOOBIGWIDTH               0x88760037L
#define DDERR_UNSUPPORTEDFORMAT         0x88760038L
#define DDERR_UNSUPPORTEDMASK           0x88760039L
#define DDERR_INVALIDSTREAM             0x8876003AL
#define DDERR_VERTICALBLANKINPROGRESS   0x8876003BL
#define DDERR_XALIGN                    0x8876003CL
#define DDERR_INVALIDDIRECTDRAWGUID     0x8876003DL
#define DDERR_DIRECTDRAWALREADYCREATED  0x8876003EL
#define DDERR_NODIRECTDRAWHW            0x8876003FL
#define DDERR_PRIMARYSURFACEALREADYEXISTS 0x88760040L
#define DDERR_NOEMULATION               0x88760041L
#define DDERR_REGIONTOOSMALL            0x88760042L
#define DDERR_CLIPPERISUSINGHWND        0x88760043L
#define DDERR_NOCLIPPERATTACHED         0x88760044L
#define DDERR_NOHWND                    0x88760045L
#define DDERR_HWNDSUBCLASSED            0x88760046L
#define DDERR_HWNDALREADYSET            0x88760047L
#define DDERR_NOPALETTEATTACHED         0x88760048L
#define DDERR_NOPALETTEHW               0x88760049L
#define DDERR_BLTFASTCANTCLIP           0x8876004AL
#define DDERR_NOBLTHW                   0x8876004BL
#define DDERR_NODDROPSHW                0x8876004CL
#define DDERR_OVERLAYNOTVISIBLE         0x8876004DL
#define DDERR_NOOVERLAYDEST             0x8876004EL
#define DDERR_INVALIDPOSITION           0x8876004FL
#define DDERR_NOTAOVERLAYSURFACE        0x88760050L
#define DDERR_EXCLUSIVEMODEALREADYSET   0x88760051L
#define DDERR_NOTFLIPPABLE              0x88760052L
#define DDERR_CANTDUPLICATE             0x88760053L
#define DDERR_NOTLOCKED                 0x88760054L
#define DDERR_CANTCREATEDC              0x88760055L
#define DDERR_NODC                      0x88760056L
#define DDERR_WRONGMODE                 0x88760057L
#define DDERR_IMPLICITLYCREATED         0x88760058L
#define DDERR_NOTPALETTIZED             0x88760059L
#define DDERR_DCALREADYCREATED          0x8876005AL
#define DDERR_MOREDATA                  0x8876005BL
#define DDERR_EXPIRED                   0x8876005CL
#define DDERR_INVALIDRECT2              0x8876005DL
#define DDERR_VIDEONOTACTIVE            0x8876005EL
#define DDERR_NOACCESS                  0x8876005FL
#define DDERR_NOOPTIMIZEHW              0x88760060L
#define DDERR_NOTLOADED                 0x88760061L
#define DDERR_NOFOCUSWINDOW            0x88760062L
#define DDERR_NOTONMIPMAPSUBLEVEL      0x88760063L
#define DDERR_TESTFINISHED             0x88760064L
#define DDERR_NEWMODE                  0x88760065L
#define DDERR_D3DNOTINITIALIZED        0x88760066L
#define DDERR_UNSUPPORTEDMODE          0x88760067L
#define DDERR_NOMIPMAPHW               0x88760068L
#define DDERR_INVALIDSURFACETYPE       0x88760069L

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
    LONG GetPalette(IDirectDrawPalette **pal) { (void)pal; if(pal) *pal = nullptr; return DD_OK; }
    LONG SetColorKey(DWORD flags, DDCOLORKEY *key) { (void)flags; (void)key; return DD_OK; }
    LONG Restore() { return DD_OK; }
    LONG GetSurfaceDesc(LPDDSURFACEDESC desc) { (void)desc; return DD_OK; }
    LONG AddAttachedSurface(IDirectDrawSurface *surf) { (void)surf; return DD_OK; }
    LONG Flip(IDirectDrawSurface *surf, DWORD flags) { (void)surf; (void)flags; return DD_OK; }
    LONG GetCaps(void *caps) { (void)caps; return DD_OK; }
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
