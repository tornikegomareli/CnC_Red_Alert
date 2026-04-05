/* Stub vqaplay.h — VQA player not yet implemented */
#ifndef _VQAPLAY_H_STUB
#define _VQAPLAY_H_STUB

typedef void *VQAHandle;

typedef struct _VQAConfig {
    int Vmode;
    int VBIBit;
    int ImageWidth;
    int ImageHeight;
    int ImageBuf;
    int X1, Y1, X2, Y2;
    int FrameRate;
    int DrawRate;
    int TimerMethod;
    int DrawFlags;
    int OptionFlags;
    int NumFrameBufs;
    int NumCBBufs;
    void *VocFile;
    long AudioBuf;
    long AudioBufSize;
    int AudioRate;
    int Volume;
    int HMIBufSize;
    int DigiHandle;
    int DigiCard;
    int DigiPort;
    int DigiIRQ;
    int DigiDMA;
    long CaptureBuf;
    long EVABuf;
    void (*DrawerCallback)(unsigned char *, long);
    void (*EventHandler)(void);
    int NotifyFlags;
    int Language;
    char *CaptionFont;
} VQAConfig;

#define VQAOPTF_AUDIO 0x0001
#define VQACMD_INIT   0
#define VQACMD_CLEANUP 1
#define VQACMD_OPEN   2
#define VQACMD_CLOSE  3
#define VQACMD_READ   4
#define VQACMD_WRITE  5
#define VQACMD_SEEK   6

static inline VQAHandle *VQA_Alloc(void) { return NULL; }
static inline void VQA_Free(VQAHandle *h) { (void)h; }
static inline void VQA_Init(VQAHandle *h, long (*io)(VQAHandle*, long, void*, long)) { (void)h; (void)io; }

#endif
