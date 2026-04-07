/* Stub digitalv.h — digital video MCI types */
#ifndef _DIGITALV_H_STUB
#define _DIGITALV_H_STUB
#include "platform.h"

typedef struct {
    DWORD dwCallback;
    MCIDEVICEID wDeviceID;
    LPCSTR lpstrDeviceType;
    LPCSTR lpstrElementName;
    LPCSTR lpstrAlias;
    DWORD dwStyle;
    HWND hWndParent;
} MCI_OPEN_PARMSA, *LPMCI_OPEN_PARMSA;
#define MCI_OPEN_PARMS MCI_OPEN_PARMSA

typedef struct {
    DWORD dwCallback;
    DWORD dwFrom;
    DWORD dwTo;
} MCI_PLAY_PARMS, *LPMCI_PLAY_PARMS;

typedef struct {
    DWORD dwCallback;
} MCI_GENERIC_PARMS, *LPMCI_GENERIC_PARMS;

#define MCI_OPEN_TYPE       0x00002000L
#define MCI_OPEN_ELEMENT    0x00000200L
#define MCI_DGV_OPEN_PARENT 0x00020000L
#define MCI_DGV_OPEN_WS     0x00010000L
#define MCI_WAIT            0x00000002L
#define MCI_NOTIFY          0x00000001L
#define MCI_DGV_PLAY_REPEAT 0x00010000L

#endif
