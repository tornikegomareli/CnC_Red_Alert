/*
 * platform.h — Master Win32 compatibility shim for macOS port
 * Provides Windows types, constants, and function stubs so the original
 * Red Alert source can compile under clang on macOS.
 */

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
/* strcasecmp/strncasecmp provided by strings.h above */
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <dirent.h>
#include <fnmatch.h>

// ============================================================================
// Additional basic types
// ============================================================================
typedef unsigned char   UBYTE;
typedef unsigned short  UWORD;

// ============================================================================
// POSIX compatibility macros
// ============================================================================
#ifndef O_BINARY
#define O_BINARY 0
#endif
#ifndef _READ
#define _READ  1
#endif
#ifndef _WRITE
#define _WRITE 2
#endif

// Case-insensitive string comparison
#define stricmp  strcasecmp
#define strnicmp strncasecmp

// wsprintf -> sprintf
#define wsprintf sprintf

// filelength() implementation via fstat
static inline long _filelength_impl(int fd) {
    struct stat st;
    if (fstat(fd, &st) == -1) return -1L;
    return (long)st.st_size;
}
#define filelength(fd) _filelength_impl(fd)

// min/max macros
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

// ============================================================================
// DirectSound status bits (needed outside dsound.h)
// ============================================================================
#define DSBSTATUS_PLAYING   0x00000001
#define DSBSTATUS_LOOPING   0x00000004

// ============================================================================
// MMIO types and constants
// ============================================================================
typedef void* HMMIO;
#define MMIO_READ       0
#define MMIO_WRITE      1
#define MMIO_READWRITE  2
#define MMIO_CREATE     0x1000

// ============================================================================
// Additional Win32 file / thread / process constants
// ============================================================================
#define FILE_FLAG_OVERLAPPED        0x40000000
#define DUPLICATE_SAME_ACCESS       0x00000002
#define THREAD_ALL_ACCESS           0x1FFFFF
#define THREAD_PRIORITY_TIME_CRITICAL 15
#define ERROR_IO_PENDING            997L
#define ERROR_IO_INCOMPLETE         996L
#define DRIVE_CDROM                 5

// ============================================================================
// Additional Windows message constants
// ============================================================================
#define WM_LBUTTONDBLCLK    0x0203
#define WM_RBUTTONDBLCLK    0x0206
#define WM_MBUTTONDOWN      0x0207
#define WM_MBUTTONUP        0x0208
#define WM_MBUTTONDBLCLK    0x0209

// ============================================================================
// Modem status bits
// ============================================================================
#define MS_CTS_ON   0x0010
#define MS_DSR_ON   0x0020
#define MS_RING_ON  0x0040
#define MS_RLSD_ON  0x0080

// ============================================================================
// Comm error codes
// ============================================================================
#define CE_RXOVER   0x0001
#define CE_OVERRUN  0x0002
#define CE_RXPARITY 0x0004
#define CE_FRAME    0x0008
#define CE_IOE      0x0010
#define CE_TXFULL   0x0100

// ============================================================================
// DCB control flags
// ============================================================================
#define DTR_CONTROL_ENABLE      1
#define RTS_CONTROL_DISABLE     0
#define RTS_CONTROL_HANDSHAKE   2

// ============================================================================
// PURGE constants (additional)
// ============================================================================
#define PURGE_TXABORT   0x0001
#define PURGE_RXABORT   0x0002

#ifdef __cplusplus
extern "C" {
#endif

// ============================================================================
// Basic Windows types
// ============================================================================
#ifndef _WINDEF_
#define _WINDEF_

// Note: WWSTD.H defines BOOL as a macro (#define BOOL int)
// so we only typedef if it hasn't been macrodefined
#ifndef BOOL
typedef int                 BOOL;
#endif
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;
typedef unsigned int        UINT;
typedef int                 INT;
typedef long                LONG;
typedef unsigned long       ULONG;
typedef short               SHORT;
typedef unsigned short      USHORT;
typedef char                CHAR;
typedef unsigned char       UCHAR;
typedef float               FLOAT;

#ifndef VOID
#define VOID void
#endif

typedef void                *LPVOID;
typedef const void          *LPCVOID;
typedef char                *LPSTR;
typedef const char          *LPCSTR;
typedef BYTE                *LPBYTE;
typedef WORD                *LPWORD;
typedef DWORD               *LPDWORD;
typedef LONG                *LPLONG;
typedef int                 *LPINT;
typedef BOOL                *LPBOOL;

typedef void                *HANDLE;
typedef void                *HWND;
typedef void                *HINSTANCE;
typedef void                *HMODULE;
typedef void                *HDC;
typedef void                *HBITMAP;
typedef void                *HPALETTE;
typedef void                *HBRUSH;
typedef void                *HFONT;
typedef void                *HICON;
typedef void                *HCURSOR;
typedef void                *HMENU;
typedef void                *HGLOBAL;
typedef long                HRESULT;
typedef void                *HKEY;
typedef long                LPARAM;
typedef unsigned long       WPARAM;
typedef long                LRESULT;
typedef UINT                MMRESULT;

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)
#endif

#define PASCAL
#define CALLBACK
#define WINAPI
#define FAR
#define NEAR
#define _export
#define _cdecl
#ifndef __cdecl
#define __cdecl
#endif

#define MAX_PATH            260
#define _MAX_PATH           260
#define _MAX_FNAME          256
#define _MAX_EXT            256
#define _MAX_DIR            256
#define _MAX_DRIVE          3

// macOS defines BIG_ENDIAN as a constant (4321) for comparison with BYTE_ORDER.
// The game code uses #ifdef BIG_ENDIAN to mean "this is a big-endian platform",
// which is always true on macOS. Undefine it so the little-endian code path is used.
#ifdef BIG_ENDIAN
#undef BIG_ENDIAN
#endif

// Useful macros
#ifndef LOWORD
#define LOWORD(l) ((WORD)((DWORD)(l) & 0xffff))
#endif
#ifndef HIWORD
#define HIWORD(l) ((WORD)((DWORD)(l) >> 16))
#endif
#ifndef LOBYTE
#define LOBYTE(w) ((BYTE)((WORD)(w) & 0xff))
#endif
#ifndef HIBYTE
#define HIBYTE(w) ((BYTE)((WORD)(w) >> 8))
#endif
#ifndef MAKELONG
#define MAKELONG(a, b) ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#endif
#ifndef MAKEWORD
#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#endif

// Access mode constants
#ifndef GENERIC_READ
#define GENERIC_READ        0x80000000L
#define GENERIC_WRITE       0x40000000L
#endif
#define FILE_SHARE_READ     0x00000001
#define FILE_SHARE_WRITE    0x00000002
#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define FILE_ATTRIBUTE_NORMAL    0x80
#define FILE_ATTRIBUTE_READONLY  0x00000001
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_BEGIN          0
#define FILE_CURRENT        1
#define FILE_END            2

// Error codes
#define ERROR_SUCCESS       0L
#define ERROR_FILE_NOT_FOUND 2L
#define ERROR_ACCESS_DENIED 5L
#define NO_ERROR            0L

// Memory allocation
#define GMEM_FIXED          0x0000
#define GMEM_ZEROINIT       0x0040
#define GPTR                (GMEM_FIXED | GMEM_ZEROINIT)

#endif // _WINDEF_

// ============================================================================
// Windows structures
// ============================================================================

typedef struct _OVERLAPPED {
    DWORD Internal;
    DWORD InternalHigh;
    DWORD Offset;
    DWORD OffsetHigh;
    HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *LPFILETIME;

// Bitmap structures
#pragma pack(push, 2)
typedef struct tagBITMAPFILEHEADER {
    WORD  bfType;
    DWORD bfSize;
    WORD  bfReserved1;
    WORD  bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER;
#pragma pack(pop)

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG  biWidth;
    LONG  biHeight;
    WORD  biPlanes;
    WORD  biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG  biXPelsPerMeter;
    LONG  biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD          bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO;

#define BI_RGB 0L

// Serial communication stubs
typedef struct _DCB {
    DWORD DCBlength;
    DWORD BaudRate;
    DWORD fBinary:1;
    DWORD fParity:1;
    DWORD fOutxCtsFlow:1;
    DWORD fOutxDsrFlow:1;
    DWORD fDtrControl:2;
    DWORD fDsrSensitivity:1;
    DWORD fTXContinueOnXoff:1;
    DWORD fOutX:1;
    DWORD fInX:1;
    DWORD fErrorChar:1;
    DWORD fNull:1;
    DWORD fRtsControl:2;
    DWORD fAbortOnError:1;
    DWORD fDummy2:17;
    WORD wReserved;
    WORD XonLim;
    WORD XoffLim;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
    char XonChar;
    char XoffChar;
    char ErrorChar;
    char EofChar;
    char EvtChar;
    WORD wReserved1;
} DCB, *LPDCB;

typedef struct _COMMTIMEOUTS {
    DWORD ReadIntervalTimeout;
    DWORD ReadTotalTimeoutMultiplier;
    DWORD ReadTotalTimeoutConstant;
    DWORD WriteTotalTimeoutMultiplier;
    DWORD WriteTotalTimeoutConstant;
} COMMTIMEOUTS, *LPCOMMTIMEOUTS;

typedef struct _COMSTAT {
    DWORD fCtsHold;
    DWORD cbInQue;
    DWORD cbOutQue;
} COMSTAT, *LPCOMSTAT;

typedef struct _BY_HANDLE_FILE_INFORMATION {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD nNumberOfLinks;
    DWORD nFileIndexHigh;
    DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;

static inline BOOL GetFileInformationByHandle(HANDLE h, BY_HANDLE_FILE_INFORMATION *info) {
    (void)h; (void)info; return FALSE;
}

// Serial comm stubs
static inline BOOL GetCommState(HANDLE h, LPDCB d) { (void)h; (void)d; return FALSE; }
static inline BOOL SetCommState(HANDLE h, LPDCB d) { (void)h; (void)d; return FALSE; }
static inline BOOL SetCommTimeouts(HANDLE h, LPCOMMTIMEOUTS t) { (void)h; (void)t; return FALSE; }
static inline BOOL SetCommMask(HANDLE h, DWORD m) { (void)h; (void)m; return FALSE; }
static inline BOOL ClearCommError(HANDLE h, LPDWORD e, LPCOMSTAT s) { (void)h; (void)e; (void)s; return FALSE; }
static inline BOOL PurgeComm(HANDLE h, DWORD f) { (void)h; (void)f; return FALSE; }
static inline BOOL EscapeCommFunction(HANDLE h, DWORD f) { (void)h; (void)f; return FALSE; }
static inline BOOL SetupComm(HANDLE h, DWORD in, DWORD out) { (void)h; (void)in; (void)out; return FALSE; }
static inline BOOL WaitCommEvent(HANDLE h, LPDWORD e, void *o) { (void)h; (void)e; (void)o; return FALSE; }
static inline BOOL GetCommModemStatus(HANDLE h, LPDWORD s) { (void)h; (void)s; return FALSE; }
#define PURGE_TXCLEAR 0x0004
#define PURGE_RXCLEAR 0x0008
#define SETDTR 5
#define CLRDTR 6
#define EV_RXCHAR 0x0001

typedef struct tagRECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *LPRECT;

typedef struct tagPOINT {
    LONG x;
    LONG y;
} POINT, *LPPOINT;

typedef struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
} MSG, *LPMSG;

typedef struct tagPALETTEENTRY {
    BYTE peRed;
    BYTE peGreen;
    BYTE peBlue;
    BYTE peFlags;
} PALETTEENTRY, *LPPALETTEENTRY;

typedef struct tagWNDCLASS {
    UINT style;
    void *lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR lpszMenuName;
    LPCSTR lpszClassName;
} WNDCLASS, *LPWNDCLASS;

// ============================================================================
// Windows message constants
// ============================================================================
#define WM_USER             0x0400
#define WM_DESTROY          0x0002
#define WM_CREATE           0x0001
#define WM_PAINT            0x000F
#define WM_CLOSE            0x0010
#define WM_QUIT             0x0012
#define WM_KEYDOWN          0x0100
#define WM_KEYUP            0x0101
#define WM_SYSKEYDOWN       0x0104
#define WM_SYSKEYUP         0x0105
#define WM_CHAR             0x0102
#define WM_SYSCOMMAND       0x0112
#define WM_TIMER            0x0113
#define WM_ACTIVATEAPP      0x001C
#define WM_LBUTTONDOWN      0x0201
#define WM_LBUTTONUP        0x0202
#define WM_RBUTTONDOWN      0x0204
#define WM_RBUTTONUP        0x0205
#define WM_MOUSEMOVE        0x0200
#define WM_SETCURSOR        0x0020
#define WM_ERASEBKGND       0x0014

// Virtual key codes
#define VK_LBUTTON          0x01
#define VK_RBUTTON          0x02
#define VK_MBUTTON          0x04
#define VK_SHIFT            0x10
#define VK_CONTROL          0x11
#define VK_MENU             0x12
#define VK_CAPITAL          0x14
#define VK_NUMLOCK          0x90
#define VK_SCROLL           0x91
#define VK_RETURN           0x0D
#define VK_ESCAPE           0x1B
#define VK_SPACE            0x20
#define VK_LEFT             0x25
#define VK_UP               0x26
#define VK_RIGHT            0x27
#define VK_DOWN             0x28
#define VK_INSERT           0x2D
#define VK_DELETE           0x2E
#define VK_HOME             0x24
#define VK_END              0x23
#define VK_PRIOR            0x21
#define VK_NEXT             0x22
#define VK_SELECT           0x29
#define VK_F1               0x70
#define VK_F2               0x71
#define VK_F3               0x72
#define VK_F4               0x73
#define VK_F5               0x74
#define VK_F6               0x75
#define VK_F7               0x76
#define VK_F8               0x77
#define VK_F9               0x78
#define VK_F10              0x79
#define VK_F11              0x7A
#define VK_F12              0x7B
#define VK_NUMPAD0          0x60
#define VK_NUMPAD1          0x61
#define VK_NUMPAD2          0x62
#define VK_NUMPAD3          0x63
#define VK_NUMPAD4          0x64
#define VK_NUMPAD5          0x65
#define VK_NUMPAD6          0x66
#define VK_NUMPAD7          0x67
#define VK_NUMPAD8          0x68
#define VK_NUMPAD9          0x69
#define VK_MULTIPLY         0x6A
#define VK_ADD              0x6B
#define VK_SUBTRACT         0x6D
#define VK_DECIMAL          0x6E
#define VK_DIVIDE           0x6F
#define VK_TAB              0x09
#define VK_BACK             0x08

// ShowWindow commands
#define SW_SHOW             5
#define SW_SHOWNORMAL       1
#define SW_SHOWMAXIMIZED    3
#define SW_HIDE             0

// MessageBox styles
#define MB_OK               0x00000000L
#define MB_YESNO            0x00000004L
#define MB_ICONEXCLAMATION  0x00000030L
#define MB_ICONHAND         0x00000010L
#define MB_SETFOREGROUND    0x00010000L
#define IDOK                1
#define IDYES               6
#define IDNO                7

// Window styles
#define WS_OVERLAPPEDWINDOW 0x00CF0000L
#define WS_POPUP            0x80000000L
#define WS_VISIBLE          0x10000000L
#define WS_EX_TOPMOST       0x00000008L
#define CW_USEDEFAULT       0x80000000

// Timer
#define TIME_PERIODIC       0x0001
typedef void (CALLBACK *LPTIMECALLBACK)(UINT, UINT, DWORD, DWORD, DWORD);

// Clipboard format
#define CS_HREDRAW          0x0002
#define CS_VREDRAW          0x0001

// Registry
#define HKEY_LOCAL_MACHINE  ((HKEY)(intptr_t)0x80000002)
#define KEY_READ            0x20019
#define REG_SZ              1
#define ERROR_MORE_DATA     234L

// Critical section
typedef struct _CRITICAL_SECTION {
    void *dummy;
} CRITICAL_SECTION, *LPCRITICAL_SECTION;

// ============================================================================
// Win32 function stubs (declared for compilation, implemented as needed)
// ============================================================================

// Window management
static inline HWND FindWindowA(LPCSTR cls, LPCSTR name) { (void)cls; (void)name; return NULL; }
#define FindWindow FindWindowA
static inline BOOL ShowWindow(HWND h, int cmd) { (void)h; (void)cmd; return FALSE; }
static inline BOOL UpdateWindow(HWND h) { (void)h; return FALSE; }
static inline BOOL SetForegroundWindow(HWND h) { (void)h; return FALSE; }
static inline BOOL DestroyWindow(HWND h) { (void)h; return FALSE; }
static inline void PostQuitMessage(int code) { (void)code; }
static inline LRESULT DefWindowProcA(HWND h, UINT msg, WPARAM w, LPARAM l) { (void)h; (void)msg; (void)w; (void)l; return 0; }
#define DefWindowProc DefWindowProcA
static inline BOOL GetClientRect(HWND h, LPRECT r) { (void)h; (void)r; return FALSE; }
static inline BOOL GetWindowRect(HWND h, LPRECT r) { (void)h; (void)r; return FALSE; }
static inline BOOL MoveWindow(HWND h, int x, int y, int w, int ht, BOOL r) { (void)h; (void)x; (void)y; (void)w; (void)ht; (void)r; return FALSE; }
static inline BOOL InvalidateRect(HWND h, const RECT *r, BOOL e) { (void)h; (void)r; (void)e; return FALSE; }
static inline LONG SetWindowLongA(HWND h, int i, LONG v) { (void)h; (void)i; (void)v; return 0; }
#define SetWindowLong SetWindowLongA
static inline LONG GetWindowLongA(HWND h, int i) { (void)h; (void)i; return 0; }
#define GetWindowLong GetWindowLongA
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)

// Message handling
static inline BOOL PeekMessageA(LPMSG m, HWND h, UINT mn, UINT mx, UINT rm) { (void)m; (void)h; (void)mn; (void)mx; (void)rm; return FALSE; }
#define PeekMessage PeekMessageA
static inline BOOL GetMessageA(LPMSG m, HWND h, UINT mn, UINT mx) { (void)m; (void)h; (void)mn; (void)mx; return FALSE; }
#define GetMessage GetMessageA
static inline BOOL TranslateMessage(const MSG *m) { (void)m; return FALSE; }
static inline LRESULT DispatchMessageA(const MSG *m) { (void)m; return 0; }
#define DispatchMessage DispatchMessageA
static inline BOOL PostMessageA(HWND h, UINT m, WPARAM w, LPARAM l) { (void)h; (void)m; (void)w; (void)l; return FALSE; }
#define PostMessage PostMessageA
static inline LRESULT SendMessageA(HWND h, UINT m, WPARAM w, LPARAM l) { (void)h; (void)m; (void)w; (void)l; return 0; }
#define SendMessage SendMessageA
static inline UINT RegisterWindowMessageA(LPCSTR s) { (void)s; return WM_USER + 200; }
#define RegisterWindowMessage RegisterWindowMessageA
#define PM_REMOVE 0x0001
#define PM_NOREMOVE 0x0000

// Window class
static inline int RegisterClassA(const WNDCLASS *wc) { (void)wc; return 1; }
#define RegisterClass RegisterClassA
static inline HWND CreateWindowExA(DWORD ex, LPCSTR cls, LPCSTR name, DWORD style,
    int x, int y, int w, int h, HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    (void)ex; (void)cls; (void)name; (void)style; (void)x; (void)y; (void)w; (void)h;
    (void)parent; (void)menu; (void)inst; (void)param; return NULL;
}
#define CreateWindowEx CreateWindowExA
#define CreateWindow(cls, name, style, x, y, w, h, parent, menu, inst, param) \
    CreateWindowExA(0, cls, name, style, x, y, w, h, parent, menu, inst, param)

// Input
static inline SHORT GetKeyState(int vk) { (void)vk; return 0; }
/* GetAsyncKeyState provided by raylib_input.cpp */
SHORT GetAsyncKeyState(int vk);
static inline SHORT VkKeyScanA(CHAR c) { (void)c; return -1; }
#define VkKeyScan VkKeyScanA
static inline BOOL ClipCursor(const RECT *r) { (void)r; return FALSE; }
static inline BOOL SetCursorPos(int x, int y) { (void)x; (void)y; return FALSE; }
static inline BOOL GetCursorPos(LPPOINT p) { (void)p; return FALSE; }
static inline HCURSOR SetCursor(HCURSOR h) { (void)h; return NULL; }
static inline int ShowCursor(BOOL show) { (void)show; return 0; }
static inline HCURSOR LoadCursorA(HINSTANCE h, LPCSTR n) { (void)h; (void)n; return NULL; }
#define LoadCursor LoadCursorA
#define IDC_ARROW ((LPCSTR)(intptr_t)32512)

// MessageBox
static inline int MessageBoxA(HWND h, LPCSTR txt, LPCSTR cap, UINT type) {
    (void)h; (void)type;
    fprintf(stderr, "MessageBox [%s]: %s\n", cap ? cap : "", txt ? txt : "");
    return IDOK;
}
#define MessageBox MessageBoxA

// Timer
static inline DWORD GetTickCount(void) { return 0; }
static inline DWORD timeGetTime(void) { return 0; }
static inline MMRESULT timeBeginPeriod(UINT p) { (void)p; return 0; }
static inline MMRESULT timeEndPeriod(UINT p) { (void)p; return 0; }
static inline MMRESULT timeSetEvent(UINT d, UINT r, LPTIMECALLBACK cb, DWORD u, UINT f) {
    (void)d; (void)r; (void)cb; (void)u; (void)f; return 0;
}
static inline MMRESULT timeKillEvent(UINT id) { (void)id; return 0; }

// File I/O (stubs — will be replaced by POSIX in Phase 2)
/*
 * File I/O — POSIX implementation of Win32 file API
 * HANDLE stores a file descriptor as (void*)(intptr_t)(fd+1), with NULL = invalid.
 * We add 1 so that fd=0 (stdin) maps to non-NULL.
 */
#define _FD_TO_HANDLE(fd) ((HANDLE)(intptr_t)((fd) + 1))
#define _HANDLE_TO_FD(h)  ((int)((intptr_t)(h) - 1))
#define _IS_VALID_HANDLE(h) ((h) != NULL && (h) != INVALID_HANDLE_VALUE)

static inline HANDLE CreateFileA(LPCSTR name, DWORD access, DWORD share,
    void *sec, DWORD disp, DWORD flags, HANDLE tmpl) {
    (void)share; (void)sec; (void)flags; (void)tmpl;
    if (!name) return INVALID_HANDLE_VALUE;

    /* Normalize backslash paths */
    char path[512];
    strncpy(path, name, sizeof(path)-1);
    path[sizeof(path)-1] = '\0';
    for (char *p = path; *p; p++) { if (*p == '\\') *p = '/'; }

    int oflags = 0;
    if ((access & (GENERIC_READ|GENERIC_WRITE)) == (GENERIC_READ|GENERIC_WRITE))
        oflags = O_RDWR;
    else if (access & GENERIC_WRITE)
        oflags = O_WRONLY;
    else
        oflags = O_RDONLY;

    if (disp == CREATE_ALWAYS) oflags |= O_CREAT | O_TRUNC;
    else if (disp == OPEN_ALWAYS) oflags |= O_CREAT;
    /* OPEN_EXISTING: no extra flags */

    int fd = open(path, oflags, 0666);
    if (fd < 0) return INVALID_HANDLE_VALUE;
    return _FD_TO_HANDLE(fd);
}
#define CreateFile CreateFileA

static inline BOOL ReadFile(HANDLE h, LPVOID buf, DWORD bytes, LPDWORD bytesRead, void *ovl) {
    (void)ovl;
    if (!_IS_VALID_HANDLE(h)) return FALSE;
    ssize_t n = read(_HANDLE_TO_FD(h), buf, bytes);
    if (n < 0) { if (bytesRead) *bytesRead = 0; return FALSE; }
    if (bytesRead) *bytesRead = (DWORD)n;
    return TRUE;
}

static inline BOOL WriteFile(HANDLE h, LPCVOID buf, DWORD bytes, LPDWORD bytesWritten, void *ovl) {
    (void)ovl;
    if (!_IS_VALID_HANDLE(h)) return FALSE;
    ssize_t n = write(_HANDLE_TO_FD(h), buf, bytes);
    if (n < 0) { if (bytesWritten) *bytesWritten = 0; return FALSE; }
    if (bytesWritten) *bytesWritten = (DWORD)n;
    return TRUE;
}

static inline DWORD SetFilePointer(HANDLE h, LONG dist, LPLONG high, DWORD method) {
    (void)high;
    if (!_IS_VALID_HANDLE(h)) return 0xFFFFFFFF;
    int whence = SEEK_SET;
    if (method == FILE_CURRENT) whence = SEEK_CUR;
    else if (method == FILE_END) whence = SEEK_END;
    off_t pos = lseek(_HANDLE_TO_FD(h), dist, whence);
    if (pos < 0) return 0xFFFFFFFF;
    return (DWORD)pos;
}

static inline BOOL CloseHandle(HANDLE h) {
    if (!_IS_VALID_HANDLE(h)) return FALSE;
    return close(_HANDLE_TO_FD(h)) == 0;
}

static inline DWORD GetFileSize(HANDLE h, LPDWORD high) {
    if (high) *high = 0;
    if (!_IS_VALID_HANDLE(h)) return 0xFFFFFFFF;
    struct stat st;
    if (fstat(_HANDLE_TO_FD(h), &st) != 0) return 0xFFFFFFFF;
    return (DWORD)st.st_size;
}

static inline BOOL DeleteFileA(LPCSTR name) {
    if (!name) return FALSE;
    char path[512];
    strncpy(path, name, sizeof(path)-1);
    path[sizeof(path)-1] = '\0';
    for (char *p = path; *p; p++) { if (*p == '\\') *p = '/'; }
    return unlink(path) == 0;
}
#define DeleteFile DeleteFileA

static inline DWORD GetFileAttributesA(LPCSTR name) {
    if (!name) return 0xFFFFFFFF;
    char path[512];
    strncpy(path, name, sizeof(path)-1);
    path[sizeof(path)-1] = '\0';
    for (char *p = path; *p; p++) { if (*p == '\\') *p = '/'; }
    struct stat st;
    if (stat(path, &st) != 0) return 0xFFFFFFFF;
    DWORD attr = FILE_ATTRIBUTE_NORMAL;
    if (S_ISDIR(st.st_mode)) attr |= FILE_ATTRIBUTE_DIRECTORY;
    if (!(st.st_mode & S_IWUSR)) attr |= FILE_ATTRIBUTE_READONLY;
    return attr;
}
#define GetFileAttributes GetFileAttributesA
static inline DWORD GetLastError(void) { return 0; }
static inline void SetLastError(DWORD err) { (void)err; }
static inline DWORD GetShortPathNameA(LPCSTR l, LPSTR s, DWORD sz) { (void)l; (void)s; (void)sz; return 0; }
#define GetShortPathName GetShortPathNameA

// FindFirstFile / FindNextFile
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    char cFileName[MAX_PATH];
    char cAlternateFileName[14];
    DWORD nFileSizeLow;
    DWORD nFileSizeHigh;
    FILETIME ftCreationTime;
    FILETIME ftLastWriteTime;
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
#define WIN32_FIND_DATA WIN32_FIND_DATAA
static inline HANDLE FindFirstFileA(LPCSTR path, LPWIN32_FIND_DATAA data) { (void)path; (void)data; return INVALID_HANDLE_VALUE; }
#define FindFirstFile FindFirstFileA
static inline BOOL FindNextFileA(HANDLE h, LPWIN32_FIND_DATAA data) { (void)h; (void)data; return FALSE; }
#define FindNextFile FindNextFileA
static inline BOOL FindClose(HANDLE h) { (void)h; return FALSE; }

// Memory
static inline HGLOBAL GlobalAlloc(UINT flags, size_t size) { (void)flags; return malloc(size); }
static inline HGLOBAL GlobalFree(HGLOBAL h) { free(h); return NULL; }
static inline LPVOID GlobalLock(HGLOBAL h) { return h; }
static inline BOOL GlobalUnlock(HGLOBAL h) { (void)h; return FALSE; }

// System info
static inline void GetSystemInfo(void *info) { (void)info; }
static inline DWORD GetCurrentDirectory(DWORD sz, LPSTR buf) { (void)sz; (void)buf; return 0; }
static inline BOOL SetCurrentDirectory(LPCSTR path) { (void)path; return FALSE; }
static inline UINT GetSystemDirectoryA(LPSTR buf, UINT sz) { (void)buf; (void)sz; return 0; }
#define GetSystemDirectory GetSystemDirectoryA
static inline int GetSystemMetrics(int idx) { (void)idx; return 0; }
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1

// Registry stubs
static inline LONG RegOpenKeyExA(HKEY key, LPCSTR sub, DWORD opts, DWORD access, HKEY *result) {
    (void)key; (void)sub; (void)opts; (void)access; (void)result; return 2; // ERROR_FILE_NOT_FOUND
}
#define RegOpenKeyEx RegOpenKeyExA
static inline LONG RegQueryValueExA(HKEY key, LPCSTR name, LPDWORD reserved, LPDWORD type, LPBYTE data, LPDWORD size) {
    (void)key; (void)name; (void)reserved; (void)type; (void)data; (void)size; return 2;
}
#define RegQueryValueEx RegQueryValueExA
static inline LONG RegCloseKey(HKEY key) { (void)key; return 0; }

// Profile (INI) stubs
static inline DWORD GetPrivateProfileStringA(LPCSTR sec, LPCSTR key, LPCSTR def, LPSTR ret, DWORD sz, LPCSTR file) {
    (void)sec; (void)key; (void)file;
    if (def && ret && sz > 0) { strncpy(ret, def, sz); ret[sz-1] = '\0'; return (DWORD)strlen(ret); }
    if (ret && sz > 0) ret[0] = '\0';
    return 0;
}
#define GetPrivateProfileString GetPrivateProfileStringA
static inline UINT GetPrivateProfileIntA(LPCSTR sec, LPCSTR key, INT def, LPCSTR file) {
    (void)sec; (void)key; (void)file; return def;
}
#define GetPrivateProfileInt GetPrivateProfileIntA
static inline BOOL WritePrivateProfileStringA(LPCSTR sec, LPCSTR key, LPCSTR val, LPCSTR file) {
    (void)sec; (void)key; (void)val; (void)file; return FALSE;
}
#define WritePrivateProfileString WritePrivateProfileStringA

// Critical section stubs
static inline void InitializeCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }
static inline void DeleteCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }
static inline void EnterCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }
static inline void LeaveCriticalSection(LPCRITICAL_SECTION cs) { (void)cs; }

// Misc
static inline void Sleep(DWORD ms) { usleep(ms * 1000); }
static inline void OutputDebugStringA(LPCSTR s) { (void)s; }
#define OutputDebugString OutputDebugStringA
static inline HMODULE GetModuleHandleA(LPCSTR name) { (void)name; return NULL; }
#define GetModuleHandle GetModuleHandleA
static inline HMODULE LoadLibraryA(LPCSTR name) { (void)name; return NULL; }
#define LoadLibrary LoadLibraryA
static inline BOOL FreeLibrary(HMODULE h) { (void)h; return FALSE; }
static inline void *GetProcAddress(HMODULE h, LPCSTR name) { (void)h; (void)name; return NULL; }
static inline DWORD GetCurrentProcessId(void) { return (DWORD)getpid(); }
static inline HANDLE GetCurrentProcess(void) { return NULL; }
static inline HANDLE GetCurrentThread(void) { return NULL; }
static inline BOOL DuplicateHandle(HANDLE src, HANDLE srcH, HANDLE dst, HANDLE *out, DWORD access, BOOL inherit, DWORD opts) {
    (void)src; (void)srcH; (void)dst; (void)out; (void)access; (void)inherit; (void)opts; return FALSE;
}
static inline BOOL SetThreadPriority(HANDLE h, int pri) { (void)h; (void)pri; return FALSE; }
static inline HANDLE CreateEventA(void *sec, BOOL manual, BOOL init, LPCSTR name) {
    (void)sec; (void)manual; (void)init; (void)name; return NULL;
}
#define CreateEvent CreateEventA
static inline BOOL SetEvent(HANDLE h) { (void)h; return FALSE; }
static inline BOOL ResetEvent(HANDLE h) { (void)h; return FALSE; }
#ifndef INFINITE
#define INFINITE 0xFFFFFFFF
#endif
#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT  0x00000102L
static inline DWORD WaitForSingleObject(HANDLE h, DWORD ms) { (void)h; (void)ms; return 0; }
static inline BOOL GetOverlappedResult(HANDLE h, LPOVERLAPPED o, LPDWORD bytes, BOOL wait) {
    (void)h; (void)o; (void)bytes; (void)wait; return FALSE;
}
static inline UINT GetDriveTypeA(LPCSTR path) { (void)path; return 0; }
#define GetDriveType GetDriveTypeA
static inline LONG RegEnumKeyExA(HKEY key, DWORD idx, LPSTR name, LPDWORD nameSz, LPDWORD reserved, LPSTR cls, LPDWORD clsSz, void *ft) {
    (void)key; (void)idx; (void)name; (void)nameSz; (void)reserved; (void)cls; (void)clsSz; (void)ft; return 2;
}
#define RegEnumKeyEx RegEnumKeyExA
static inline LONG RegQueryInfoKeyA(HKEY key, LPSTR cls, LPDWORD clsSz, LPDWORD reserved,
    LPDWORD subKeys, LPDWORD maxSubKey, LPDWORD maxClass, LPDWORD values,
    LPDWORD maxValueName, LPDWORD maxValueData, LPDWORD secDesc, void *ft) {
    (void)key; (void)cls; (void)clsSz; (void)reserved; (void)subKeys; (void)maxSubKey;
    (void)maxClass; (void)values; (void)maxValueName; (void)maxValueData; (void)secDesc; (void)ft;
    return 2;
}
#define RegQueryInfoKey RegQueryInfoKeyA
static inline int GetDeviceCaps(HDC h, int idx) { (void)h; (void)idx; return 0; }

// GDI
static inline HDC GetDC(HWND h) { (void)h; return NULL; }
static inline int ReleaseDC(HWND h, HDC dc) { (void)h; (void)dc; return 0; }
#define BITSPIXEL 12
#define PLANES 14
#define SRCCOPY 0x00CC0020L

// Non-standard C functions
static inline char *itoa(int value, char *str, int base) {
    if (base == 10) { sprintf(str, "%d", value); }
    else if (base == 16) { sprintf(str, "%x", value); }
    else { sprintf(str, "%d", value); }
    return str;
}
static inline char *ltoa(long value, char *str, int base) {
    if (base == 10) { sprintf(str, "%ld", value); }
    else if (base == 16) { sprintf(str, "%lx", value); }
    else { sprintf(str, "%ld", value); }
    return str;
}

// OLE/COM stubs
static inline LONG OleInitialize(LPVOID reserved) { (void)reserved; return 0; }
static inline void OleUninitialize(void) {}
static inline LONG CoInitialize(LPVOID reserved) { (void)reserved; return 0; }

// MMIO function stubs
static inline HMMIO mmioOpen(char *filename, void *info, DWORD flags) {
    (void)info;
    if (!filename) return NULL;
    const char *mode = "rb";
    if (flags & MMIO_CREATE) {
        if (flags & MMIO_READWRITE) mode = "w+b";
        else mode = "wb";
    } else if ((flags & MMIO_READWRITE) == MMIO_READWRITE) {
        mode = "r+b";
    } else if (flags & MMIO_WRITE) {
        mode = "wb";
    }
    return (HMMIO)fopen(filename, mode);
}
static inline long mmioRead(HMMIO h, char *buf, long bytes) {
    if (!h) return -1;
    return (long)fread(buf, 1, (size_t)bytes, (FILE*)h);
}
static inline long mmioWrite(HMMIO h, const char *buf, long bytes) {
    if (!h) return -1;
    return (long)fwrite(buf, 1, (size_t)bytes, (FILE*)h);
}
static inline long mmioSeek(HMMIO h, long offset, int origin) {
    if (!h) return -1;
    fseek((FILE*)h, offset, origin);
    return ftell((FILE*)h);
}
static inline int mmioClose(HMMIO h, UINT flags) {
    (void)flags;
    if (!h) return -1;
    return fclose((FILE*)h);
}
static inline int mmioSetBuffer(HMMIO h, char *buf, long sz, UINT flags) {
    (void)h; (void)buf; (void)sz; (void)flags; return 0;
}

// DDE stubs
typedef void *HSZ;
typedef void *HCONV;
typedef void *HDDEDATA;
typedef DWORD HCONVLIST;
#define XCLASS_FLAGS 0x4000
#define XTYP_CONNECT (0x0060 | XCLASS_FLAGS)
#define XTYP_ADVDATA 0x0010
#define XTYP_DISCONNECT 0x00C0
#define XTYP_POKE (0x0090 | XCLASS_FLAGS)
#define XTYP_REQUEST (0x00B0 | XCLASS_FLAGS)
#define DMLERR_NO_ERROR 0
typedef HDDEDATA (CALLBACK *PFNCALLBACK)(UINT, UINT, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD);
static inline UINT DdeInitializeA(LPDWORD id, PFNCALLBACK cb, DWORD flags, DWORD res) {
    (void)id; (void)cb; (void)flags; (void)res; return DMLERR_NO_ERROR;
}
#define DdeInitialize DdeInitializeA
static inline BOOL DdeUninitialize(DWORD id) { (void)id; return TRUE; }
static inline HSZ DdeCreateStringHandleA(DWORD id, LPCSTR str, int cp) { (void)id; (void)str; (void)cp; return NULL; }
#define DdeCreateStringHandle DdeCreateStringHandleA
static inline BOOL DdeFreeStringHandle(DWORD id, HSZ hsz) { (void)id; (void)hsz; return TRUE; }
static inline HCONV DdeConnect(DWORD id, HSZ svc, HSZ topic, void *cc) { (void)id; (void)svc; (void)topic; (void)cc; return NULL; }
static inline BOOL DdeDisconnect(HCONV conv) { (void)conv; return TRUE; }
static inline HDDEDATA DdeNameService(DWORD id, HSZ svc, HSZ reserved, UINT flags) { (void)id; (void)svc; (void)reserved; (void)flags; return NULL; }
static inline HDDEDATA DdeClientTransaction(LPBYTE data, DWORD sz, HCONV conv, HSZ item, UINT fmt, UINT type, DWORD timeout, LPDWORD result) {
    (void)data; (void)sz; (void)conv; (void)item; (void)fmt; (void)type; (void)timeout; (void)result; return NULL;
}
static inline DWORD DdeGetData(HDDEDATA data, LPBYTE buf, DWORD max, DWORD off) { (void)data; (void)buf; (void)max; (void)off; return 0; }
#define DNS_REGISTER 0x0001
#define DNS_UNREGISTER 0x0002
#define CP_WINANSI 1004
#define CF_TEXT 1
#define APPCMD_FILTERINITS 0x00000020L
#define CBF_FAIL_CONNECTIONS 0x00002000
#define CBF_SKIP_ALLNOTIFICATIONS 0x003c0000

// MCI stubs
typedef UINT MCIERROR;
typedef UINT MCIDEVICEID;
#define MCI_OPEN    0x0803
#define MCI_CLOSE   0x0804
#define MCI_PLAY    0x0806
#define MCI_STOP    0x0808
#define MCI_PAUSE   0x0809
static inline MCIERROR mciSendCommandA(MCIDEVICEID id, UINT msg, DWORD flags, DWORD param) {
    (void)id; (void)msg; (void)flags; (void)param; return 0;
}
#define mciSendCommand mciSendCommandA

#ifdef __cplusplus
}
#endif

// ============================================================================
// Watcom compiler compatibility
// ============================================================================
#ifndef __WATCOMC__
// Neutralize Watcom-specific pragmas
#define pragma_off_unreferenced
// #pragma option is Borland/Watcom — ignore under clang
#endif

/* Additional types and functions discovered during compilation */

/* GDI types and functions */
typedef struct tagLOGPALETTE {
    WORD palVersion;
    WORD palNumEntries;
    PALETTEENTRY palPalEntry[1];
} LOGPALETTE, *LPLOGPALETTE;

typedef struct tagBITMAPCOREHEADER {
    DWORD bcSize;
    WORD  bcWidth;
    WORD  bcHeight;
    WORD  bcPlanes;
    WORD  bcBitCount;
} BITMAPCOREHEADER, *LPBITMAPCOREHEADER;

typedef struct tagBITMAPCOREINFO {
    BITMAPCOREHEADER bmciHeader;
    RGBQUAD bmciColors[1];
} BITMAPCOREINFO, *LPBITMAPCOREINFO;

typedef struct tagBITMAP_S {
    LONG bmType;
    LONG bmWidth;
    LONG bmHeight;
    LONG bmWidthBytes;
    WORD bmPlanes;
    WORD bmBitCount;
    LPVOID bmBits;
} BITMAP_S;
#define BITMAP BITMAP_S

typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGBTRIPLE;

typedef struct _MEMORYSTATUS {
    DWORD dwLength;
    DWORD dwMemoryLoad;
    DWORD dwTotalPhys;
    DWORD dwAvailPhys;
    DWORD dwTotalPageFile;
    DWORD dwAvailPageFile;
    DWORD dwTotalVirtual;
    DWORD dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

typedef struct _STARTUPINFOA {
    DWORD cb;
    LPSTR lpTitle;
    DWORD dwFlags;
    WORD wShowWindow;
} STARTUPINFOA;
#define STARTUPINFO STARTUPINFOA

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct tagPAINTSTRUCT {
    HDC hdc;
    BOOL fErase;
    RECT rcPaint;
    BOOL fRestore;
    BOOL fIncUpdate;
    BYTE rgbReserved[32];
} PAINTSTRUCT, *LPPAINTSTRUCT;

typedef struct _SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay;
    WORD wHour, wMinute, wSecond, wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

typedef struct _OFSTRUCT {
    BYTE cBytes;
    BYTE fFixedDisk;
    WORD nErrCode;
    char szPathName[128];
} OFSTRUCT, *LPOFSTRUCT;

struct find_t {
    char name[260];
    unsigned attrib;
    unsigned long size;
    unsigned wr_date;
    unsigned wr_time;
};

typedef BOOL (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef DWORD (CALLBACK *LPTHREAD_START_ROUTINE)(LPVOID);
typedef void *LPSECURITY_ATTRIBUTES;
typedef unsigned char *PBYTE;
typedef void *LPSOCKADDR;

/* Additional constants */
#define RGB(r,g,b) ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define SIZEPALETTE 256
#define DEFAULT_PALETTE 15
#define NUMCOLORS 24
#define DIB_RGB_COLORS 0
#define CBM_INIT 4
#define COLORONCOLOR 3
#define GDI_ERROR 0xFFFFFFFFL
#define BI_RLE8 1L
#define BI_RLE4 2L
#define OF_READ 0
#define OF_READWRITE 2
#define OF_CREATE 0x1000
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define SEM_FAILCRITICALERRORS 0x0001
#define SEM_NOOPENFILEERRORBOX 0x8000
#define SC_CLOSE 0xF060
#define SC_SCREENSAVE 0xF140
#define SW_RESTORE 9
#define SW_MINIMIZE 6
#define GHND (GMEM_FIXED | GMEM_ZEROINIT)
#define GMEM_MOVEABLE 0x0002
#define PM_NOYIELD 0x0002
#define HKEY_CLASSES_ROOT ((HKEY)(intptr_t)0x80000000)
#define MB_ICONSTOP MB_ICONHAND
#define MB_ICONQUESTION 0x00000020L
#define S_OK 0L
#define IDC_WAIT ((LPCSTR)(intptr_t)32514)
#define MAKEINTRESOURCE(i) ((LPCSTR)((DWORD)((WORD)(i))))
#define _HARDERR_FAIL 0
#define MAXGETHOSTSTRUCT 1024
#define PF_INET AF_INET

/* Missing string functions */
#define strcmpi strcasecmp
static inline void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext) {
    if (drive) drive[0] = '\0';
    if (dir) dir[0] = '\0';
    if (fname) fname[0] = '\0';
    if (ext) ext[0] = '\0';
    if (!path) return;
    const char *p = path;
    /* Find last separator */
    const char *last_sep = NULL;
    for (const char *s = p; *s; s++) { if (*s == '/' || *s == '\\') last_sep = s; }
    const char *name_start = last_sep ? last_sep + 1 : p;
    if (dir && last_sep) { int len = (int)(name_start - p); strncpy(dir, p, len); dir[len] = '\0'; }
    /* Find extension */
    const char *dot = NULL;
    for (const char *s = name_start; *s; s++) { if (*s == '.') dot = s; }
    if (dot) {
        if (fname) { int len = (int)(dot - name_start); strncpy(fname, name_start, len); fname[len] = '\0'; }
        if (ext) strcpy(ext, dot);
    } else {
        if (fname) strcpy(fname, name_start);
    }
}
static inline void _makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext) {
    if (!path) return;
    path[0] = '\0';
    if (drive && drive[0]) { strcat(path, drive); strcat(path, ":"); }
    if (dir && dir[0]) strcat(path, dir);
    if (fname && fname[0]) strcat(path, fname);
    if (ext && ext[0]) strcat(path, ext);
}
#define strupr(s) _strupr_impl(s)
#define memicmp(a,b,c) strncasecmp((const char*)(a),(const char*)(b),(c))

static inline char *_strupr_impl(char *s) { if(s) for(char *p=s;*p;p++) *p=toupper(*p); return s; }
/* _filelength_impl already defined above */

/* Missing Win32 function stubs */
static inline void GlobalMemoryStatus(LPMEMORYSTATUS s) { if(s) { s->dwTotalPhys=256*1024*1024; s->dwAvailPhys=128*1024*1024; } }
static inline UINT SetErrorMode(UINT m) { (void)m; return 0; }
static inline BOOL IsWindow(HWND h) { (void)h; return FALSE; }
static inline HWND SetFocus(HWND h) { (void)h; return NULL; }
static inline HPALETTE CreatePalette(const LOGPALETTE *lp) { (void)lp; return NULL; }
static inline HPALETTE SelectPalette(HDC dc, HPALETTE pal, BOOL bg) { (void)dc; (void)pal; (void)bg; return NULL; }
static inline UINT RealizePalette(HDC dc) { (void)dc; return 0; }
static inline HBITMAP CreateDIBitmap(HDC dc, const BITMAPINFOHEADER *h, DWORD init, const void *data, const BITMAPINFO *bi, UINT usage) { (void)dc;(void)h;(void)init;(void)data;(void)bi;(void)usage; return NULL; }
static inline BOOL DeleteObject(void *obj) { (void)obj; return FALSE; }
static inline HDC CreateCompatibleDC(HDC dc) { (void)dc; return NULL; }
static inline int StretchDIBits(HDC dc,int dx,int dy,int dw,int dh,int sx,int sy,int sw,int sh,const void *bits,const BITMAPINFO *bi,UINT usage,DWORD rop) { (void)dc;(void)dx;(void)dy;(void)dw;(void)dh;(void)sx;(void)sy;(void)sw;(void)sh;(void)bits;(void)bi;(void)usage;(void)rop; return 0; }
static inline BOOL DeleteDC(HDC dc) { (void)dc; return FALSE; }
static inline int GetObject(HANDLE h, int sz, LPVOID buf) { (void)h;(void)sz;(void)buf; return 0; }
static inline DWORD GetVersion(void) { return 0x80000005; } /* fake Win95 */
static inline void ExitProcess(UINT code) { _exit(code); }
static inline BOOL GetFileTime(HANDLE h, LPFILETIME c, LPFILETIME a, LPFILETIME w) { (void)h;(void)c;(void)a;(void)w; return FALSE; }
static inline BOOL SetFileTime(HANDLE h, const FILETIME *c, const FILETIME *a, const FILETIME *w) { (void)h;(void)c;(void)a;(void)w; return FALSE; }
static inline BOOL FileTimeToDosDateTime(const FILETIME *ft, LPWORD d, LPWORD t) { (void)ft;(void)d;(void)t; return FALSE; }
static inline BOOL DosDateTimeToFileTime(WORD d, WORD t, LPFILETIME ft) { (void)d;(void)t;(void)ft; return FALSE; }
static inline BOOL SystemTimeToFileTime(const SYSTEMTIME *st, LPFILETIME ft) { (void)st;(void)ft; return FALSE; }
static inline void GetLocalTime(LPSYSTEMTIME st) { if(st) memset(st,0,sizeof(*st)); }
static inline BOOL CreateProcessA(LPCSTR app, LPSTR cmd, void *pa, void *ta, BOOL inh, DWORD flags, void *env, LPCSTR dir, STARTUPINFOA *si, LPPROCESS_INFORMATION pi) { (void)app;(void)cmd;(void)pa;(void)ta;(void)inh;(void)flags;(void)env;(void)dir;(void)si;(void)pi; return FALSE; }
#define CreateProcess CreateProcessA
static inline BOOL TerminateThread(HANDLE h, DWORD code) { (void)h;(void)code; return FALSE; }
static inline HANDLE CreateThread(void *sa, DWORD stack, LPTHREAD_START_ROUTINE fn, LPVOID param, DWORD flags, LPDWORD id) { (void)sa;(void)stack;(void)fn;(void)param;(void)flags;(void)id; return NULL; }
static inline HDC BeginPaint(HWND h, LPPAINTSTRUCT ps) { (void)h;(void)ps; return NULL; }
static inline BOOL EndPaint(HWND h, const PAINTSTRUCT *ps) { (void)h;(void)ps; return FALSE; }
static inline HGLOBAL GlobalReAlloc(HGLOBAL h, DWORD sz, UINT flags) { (void)flags; return realloc(h, sz); }
static inline BOOL GetModuleFileNameA(HMODULE m, LPSTR buf, DWORD sz) { (void)m;(void)buf;(void)sz; return FALSE; }
#define GetModuleFileName GetModuleFileNameA
static inline UINT MapVirtualKeyA(UINT code, UINT type) { (void)code;(void)type; return 0; }
#define MapVirtualKey MapVirtualKeyA
static inline LONG RegQueryValueA(HKEY key, LPCSTR sub, LPSTR val, LPLONG sz) { (void)key;(void)sub;(void)val;(void)sz; return 2; }
#define RegQueryValue RegQueryValueA

/* DOS compatibility */
#define _dos_getdrive(d) do{ *(d)=3; }while(0)
#define _dos_setdrive(d,n) do{ (void)(d);(void)(n); }while(0)
#define _memavl() (64*1024*1024L)
#define _memmax() (64*1024*1024L)
static inline int _lread(int fd, void *buf, unsigned int sz) { return (int)read(fd, buf, sz); }
static inline int _lwrite(int fd, const void *buf, unsigned int sz) { return (int)write(fd, buf, sz); }
static inline long _llseek(int fd, long off, int origin) { return lseek(fd, off, origin); }
static inline int _lclose(int fd) { return close(fd); }

#define __stdcall
#define __declspec(x)



/* Winsock types for files that need them without including winsock.h */
/*
 * Socket types/constants are now provided by the winsock.h stub
 * (included from windows.h). No fallback stubs needed here.
 */

typedef void *FARPROC;
typedef const char *LPCTSTR;
#define LPCTSTR LPCSTR


/* Mouse function stubs (mouse.h excluded from wwlib32.h) */
static inline void Show_Mouse(void) {}
static inline void Hide_Mouse(void) {}
static inline void Conditional_Show_Mouse(void) {}
static inline void Conditional_Hide_Mouse(void) {}
static inline void Conditional_Hide_Mouse(int x1, int y1, int x2, int y2) { (void)x1; (void)y1; (void)x2; (void)y2; }
static inline void Set_Mouse_Cursor(int hotx, int hoty, void *cursor) { (void)hotx; (void)hoty; (void)cursor; }
static inline int Get_Mouse_State(void) { return 0; }

/* Audio system stubs (module excluded, functions referenced from core game) */
/* SampleType and SoundType are global variables in the original audio system,
   used as booleans to check if the sound system is initialized */
static inline int SampleType = 0;
static inline int SoundType = 0;
#define SAMPLE_NONE -1
static inline int Play_Sample(void const *sample, int pri=0, int vol=0xFF, signed short pan=0) { (void)sample;(void)pri;(void)vol;(void)pan; return -1; }
static inline int Is_Sample_Playing(void const *sample) { (void)sample; return 0; }
static inline void Stop_Sample(int handle) { (void)handle; }
static inline int Stop_Sample_Playing(void const *sample) { (void)sample; return 0; }
static inline void Sound_End(void) {}
static inline int Fade_Sample(int handle, int ticks) { (void)handle;(void)ticks; return 0; }
static inline int File_Stream_Sample_Vol(char const *name, int vol, int loop) { (void)name;(void)vol;(void)loop; return -1; }
static inline int Sample_Status(int handle) { (void)handle; return 0; }
static inline void Set_Score_Vol(int vol) { (void)vol; }
static inline int Start_Primary_Sound_Buffer(int forced=0) { (void)forced; return 0; }
static inline void Stop_Primary_Sound_Buffer(void) {}
static inline void Set_Primary_Buffer_Format(void) {}
static inline int Get_Digi_Handle(void) { return -1; }
static inline void Sound_Callback(void) {}
static inline int Audio_Init(void *hwnd, int bits, int stereo, int rate, int reverse) { (void)hwnd;(void)bits;(void)stereo;(void)rate;(void)reverse; return 0; }
typedef void (*Audio_Focus_Loss_Func_Type)(void);
static inline int StreamLowImpact = 0;

/* Westwood Online API stub — not used on macOS */
struct WolGameInfo { int iPlayerCount; };
class WolapiObject {
public:
    WolGameInfo GameInfoCurrent;
    bool bEnableNewAftermathUnits;
    WolapiObject() : GameInfoCurrent{0}, bEnableNewAftermathUnits(false) {}
};
static inline WolapiObject* pWolapi = nullptr;

/* HRESULT macro */
#ifndef FAILED
#define FAILED(hr) ((long)(hr) < 0)
#endif
#ifndef SUCCEEDED
#define SUCCEEDED(hr) ((long)(hr) >= 0)
#endif

/* Missing file attributes */
#ifndef FILE_ATTRIBUTE_DIRECTORY
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#endif
#ifndef FILE_ATTRIBUTE_HIDDEN
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#endif
#ifndef FILE_ATTRIBUTE_SYSTEM
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#endif
#ifndef FILE_ATTRIBUTE_TEMPORARY
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#endif

/* Missing string functions */
#ifndef _stricmp
#define _stricmp strcasecmp
#endif
#ifndef _strlwr
static inline char *_strlwr_impl(char *s) { if(s) for(char *p=s;*p;p++) *p=tolower(*p); return s; }
#define _strlwr _strlwr_impl
#endif

/* strrev - reverse a string in place */
static inline char *strrev(char *str) {
    if (!str) return str;
    char *p1 = str, *p2 = str;
    while (*p2) p2++;
    p2--;
    while (p1 < p2) { char c = *p1; *p1++ = *p2; *p2-- = c; }
    return str;
}

static inline void GetSystemTime(LPSYSTEMTIME st) { if(st) memset(st,0,sizeof(*st)); }
#define LINGER struct linger

/* diskfree_t */
struct diskfree_t {
    unsigned total_clusters;
    unsigned avail_clusters;
    unsigned sectors_per_cluster;
    unsigned bytes_per_sector;
};
static inline unsigned _dos_getdiskfree(unsigned drive, struct diskfree_t *d) {
    (void)drive; if(d) { d->total_clusters=1000; d->avail_clusters=500; d->sectors_per_cluster=8; d->bytes_per_sector=512; }
    return 0;
}

/* Missing Win32 stubs */
static inline int ToAscii(unsigned int vk, unsigned int scan, const unsigned char *state, unsigned short *buf, unsigned int flags) {
    (void)vk;(void)scan;(void)state;(void)buf;(void)flags; return 0;
}
static inline HICON LoadIconA(HINSTANCE h, LPCSTR name) { (void)h;(void)name; return NULL; }
#define LoadIcon LoadIconA
static inline int DialogBoxA(HINSTANCE h, LPCSTR tmpl, HWND parent, DLGPROC proc) { (void)h;(void)tmpl;(void)parent;(void)proc; return 0; }
#define DialogBox DialogBoxA
static inline BOOL GetVolumeInformationA(LPCSTR root, LPSTR vol, DWORD volsz, LPDWORD serial, LPDWORD maxcomp, LPDWORD flags, LPSTR fs, DWORD fssz) {
    (void)root;(void)vol;(void)volsz;(void)serial;(void)maxcomp;(void)flags;(void)fs;(void)fssz; return FALSE;
}
#define GetVolumeInformation GetVolumeInformationA
static inline int GetDIBits(HDC dc, HBITMAP bmp, unsigned start, unsigned lines, LPVOID bits, LPBITMAPINFO bi, unsigned usage) {
    (void)dc;(void)bmp;(void)start;(void)lines;(void)bits;(void)bi;(void)usage; return 0;
}
static inline int GetSystemPaletteEntries(HDC dc, unsigned start, unsigned count, LPPALETTEENTRY entries) {
    (void)dc;(void)start;(void)count;(void)entries; return 0;
}
static inline HANDLE GetStockObject(int obj) { (void)obj; return NULL; }
static inline int SetStretchBltMode(HDC dc, int mode) { (void)dc;(void)mode; return 0; }
static inline BOOL StretchBlt(HDC dst, int dx, int dy, int dw, int dh, HDC src, int sx, int sy, int sw, int sh, DWORD rop) {
    (void)dst;(void)dx;(void)dy;(void)dw;(void)dh;(void)src;(void)sx;(void)sy;(void)sw;(void)sh;(void)rop; return FALSE;
}
static inline int OpenFile(LPCSTR name, void *of, unsigned style) { (void)name;(void)of;(void)style; return -1; }
static inline BOOL SetCommBreak(HANDLE h) { (void)h; return FALSE; }
static inline BOOL ClearCommBreak(HANDLE h) { (void)h; return FALSE; }

/* RGB macro if not defined */
#ifndef RGB
#define RGB(r,g,b) ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

/* TarComClass forward decl */
#ifdef __cplusplus
class TarComClass;
#endif

/* GAME_VERSION */
#ifndef GAME_VERSION
#define GAME_VERSION 0x00030000
#endif

/* PCX_HEADER stub */
typedef struct { char dummy[128]; } PCX_HEADER;
static inline int Write_PCX_File(char const *name, void *buf, void *pal, int w, int h) { (void)name;(void)buf;(void)pal;(void)w;(void)h; return 0; }

/* find_t extra members */
/* These are added here but find_t is defined earlier - we can't add members after the fact.
   The code that uses wr_date/wr_time will need individual fixes. */

/* COM port constants for modem code */
#define COM1 1
#define COM2 2
#define COM3 3
#define COM4 4
#define COM5 5
#define ASSUCCESS 0
#define ASUSERABORT 1

/* HMI modem stubs */
static inline int HMWaitForOK(int timeout, void *data) { (void)timeout;(void)data; return 0; }
static inline int HMSetUpEchoRoutine(void *func) { (void)func; return 0; }

#endif // PLATFORM_H
