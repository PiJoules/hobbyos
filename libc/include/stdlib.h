#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

// abort() and exit() should never return
__attribute__((noreturn))
void abort();
__attribute__((noreturn))
void exit(int);


#ifdef __cplusplus
}
#endif

#endif
