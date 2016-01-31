#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>
#define SEEK_SET 0

typedef struct {
    int unused;
} FILE;

#ifdef __cplusplus
extern "C" {
#endif

int putchar(int);
int printf(const char*, ...);
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif
