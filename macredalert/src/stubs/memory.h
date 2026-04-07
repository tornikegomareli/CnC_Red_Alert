/* Stub memory.h — MemoryClass from proprietary library */
#ifndef _MEMORY_H_STUB
#define _MEMORY_H_STUB

#include <stdlib.h>

class MemoryClass {
public:
    void *Alloc(unsigned long size) { return malloc(size); }
    void Free(void const *ptr) { free((void*)ptr); }
    operator bool() const { return true; }
};

extern MemoryClass Mem;

#endif
