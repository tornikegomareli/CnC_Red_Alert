/* Stub dos.h — DOS-specific functions */
#ifndef _DOS_H_STUB
#define _DOS_H_STUB

#include <i86.h>

/* Provide _dos_getfileattr stub */
#define _A_NORMAL   0x00
#define _A_RDONLY   0x01
#define _A_HIDDEN   0x02
#define _A_SYSTEM   0x04
#define _A_SUBDIR   0x10
#define _A_ARCH     0x20

/* _dos_findfirst / _dos_findnext stubs */
static inline unsigned _dos_findfirst(const char *path, unsigned attr, struct find_t *ft) {
    (void)path; (void)attr; (void)ft; return 1; /* failure */
}
static inline unsigned _dos_findnext(struct find_t *ft) {
    (void)ft; return 1; /* failure */
}

#endif
