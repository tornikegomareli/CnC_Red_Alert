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
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

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
typedef void                *LPARAM;
typedef void                *WPARAM;
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
#define FILE_ATTRIBUTE_NORMAL 0x80
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
    DWORD fBinary;
    DWORD fParity;
    BYTE ByteSize;
    BYTE Parity;
    BYTE StopBits;
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
static inline SHORT GetAsyncKeyState(int vk) { (void)vk; return 0; }
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
static inline HANDLE CreateFileA(LPCSTR name, DWORD access, DWORD share,
    void *sec, DWORD disp, DWORD flags, HANDLE tmpl) {
    (void)name; (void)access; (void)share; (void)sec; (void)disp; (void)flags; (void)tmpl;
    return INVALID_HANDLE_VALUE;
}
#define CreateFile CreateFileA
static inline BOOL ReadFile(HANDLE h, LPVOID buf, DWORD bytes, LPDWORD read, void *ovl) {
    (void)h; (void)buf; (void)bytes; (void)read; (void)ovl; return FALSE;
}
static inline BOOL WriteFile(HANDLE h, LPCVOID buf, DWORD bytes, LPDWORD written, void *ovl) {
    (void)h; (void)buf; (void)bytes; (void)written; (void)ovl; return FALSE;
}
static inline DWORD SetFilePointer(HANDLE h, LONG dist, LPLONG high, DWORD method) {
    (void)h; (void)dist; (void)high; (void)method; return 0xFFFFFFFF;
}
static inline BOOL CloseHandle(HANDLE h) { (void)h; return FALSE; }
static inline DWORD GetFileSize(HANDLE h, LPDWORD high) { (void)h; (void)high; return 0xFFFFFFFF; }
static inline BOOL DeleteFileA(LPCSTR name) { (void)name; return FALSE; }
#define DeleteFile DeleteFileA
static inline DWORD GetFileAttributesA(LPCSTR name) { (void)name; return 0xFFFFFFFF; }
#define GetFileAttributes GetFileAttributesA
static inline DWORD GetLastError(void) { return 0; }
static inline void SetLastError(DWORD err) { (void)err; }
static inline DWORD GetShortPathNameA(LPCSTR l, LPSTR s, DWORD sz) { (void)l; (void)s; (void)sz; return 0; }
#define GetShortPathName GetShortPathNameA

// FindFirstFile / FindNextFile
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    char cFileName[MAX_PATH];
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

#endif // PLATFORM_H
