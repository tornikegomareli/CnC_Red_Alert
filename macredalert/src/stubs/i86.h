/* Stub i86.h — x86 inline assembly (Watcom) */
#ifndef _I86_H_STUB
#define _I86_H_STUB

union REGS {
    struct { unsigned int eax, ebx, ecx, edx, esi, edi, cflag; } x;
};

struct SREGS {
    unsigned short es, cs, ss, ds;
};

static inline int int386(int intno, union REGS *in, union REGS *out) {
    (void)intno; (void)in; (void)out; return 0;
}

static inline int int386x(int intno, union REGS *in, union REGS *out, struct SREGS *seg) {
    (void)intno; (void)in; (void)out; (void)seg; return 0;
}

#endif
