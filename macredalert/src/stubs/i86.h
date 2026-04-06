/* Stub i86.h — x86 inline assembly (Watcom) */
#ifndef _I86_H_STUB
#define _I86_H_STUB

union REGS {
    struct { unsigned int eax, ebx, ecx, edx, esi, edi, cflag; } x;
};

struct SREGS {
    unsigned short es, cs, ss, ds;
};

/* Undef macros from FUNCTION.H that clash with function declarations */
#ifdef int386
#undef int386
#endif
#ifdef int386x
#undef int386x
#endif

static inline int int386(int intno, union REGS *in, union REGS *out) {
    (void)intno; (void)in; (void)out; return 0;
}

static inline int int386x(int intno, union REGS *in, union REGS *out, struct SREGS *seg) {
    (void)intno; (void)in; (void)out; (void)seg; return 0;
}

static inline void segread(struct SREGS *s) { if(s) { s->es=0; s->cs=0; s->ss=0; s->ds=0; } }

#endif
