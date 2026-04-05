/* Stub direct.h — directory functions */
#ifndef _DIRECT_H_STUB
#define _DIRECT_H_STUB
#include <unistd.h>
#include <sys/stat.h>
#define _mkdir(path) mkdir(path, 0755)
#define _getcwd getcwd
#define _chdir chdir
#endif
