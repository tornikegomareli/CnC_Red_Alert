/* Stub winsock.h — Winsock type definitions */
#ifndef _WINSOCK_H_STUB
#define _WINSOCK_H_STUB

#include "platform.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SOCKET;
#define INVALID_SOCKET  ((SOCKET)-1)
#define SOCKET_ERROR    (-1)
#define SD_BOTH         2

#define WSADESCRIPTION_LEN  256
#define WSASYS_STATUS_LEN   128

typedef struct WSAData {
    WORD wVersion;
    WORD wHighVersion;
    char szDescription[WSADESCRIPTION_LEN + 1];
    char szSystemStatus[WSASYS_STATUS_LEN + 1];
    unsigned short iMaxSockets;
    unsigned short iMaxUdpDg;
    char *lpVendorInfo;
} WSADATA, *LPWSADATA;

// Async event helpers (Windows-specific, stubbed)
#define WSAGETSELECTEVENT(lParam)   0
#define WSAGETSELECTERROR(lParam)   0

static inline int WSAStartup(WORD ver, LPWSADATA data) { (void)ver; (void)data; return 0; }
static inline int WSACleanup(void) { return 0; }
static inline int WSAGetLastError(void) { return errno; }
static inline int WSAAsyncSelect(SOCKET s, HWND h, unsigned int msg, long events) {
    (void)s; (void)h; (void)msg; (void)events; return 0;
}
static inline HANDLE WSAAsyncGetHostByName(HWND h, unsigned int msg, const char *name, char *buf, int len) {
    (void)h; (void)msg; (void)name; (void)buf; (void)len; return NULL;
}
static inline HANDLE WSAAsyncGetHostByAddress(HWND h, unsigned int msg, const char *addr, int len, int type, char *buf, int buflen) {
    (void)h; (void)msg; (void)addr; (void)len; (void)type; (void)buf; (void)buflen; return NULL;
}
static inline int WSACancelAsyncRequest(HANDLE h) { (void)h; return 0; }
static inline int closesocket(SOCKET s) { return close(s); }
static inline int ioctlsocket(SOCKET s, long cmd, unsigned long *argp) { (void)s; (void)cmd; (void)argp; return 0; }

// Network event flags
#define FD_READ     0x01
#define FD_WRITE    0x02
#define FD_ACCEPT   0x08
#define FD_CONNECT  0x10
#define FD_CLOSE    0x20

#ifdef __cplusplus
}
#endif

#endif // _WINSOCK_H_STUB
