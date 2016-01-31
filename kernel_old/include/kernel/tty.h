#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

/**
 * Teletypewriter functions in kernel space.
 */

#include <stddef.h>

void kinitialize(void);
void kputchar(char c);
void kwrite(const char* data, size_t size);
void kwriteString(const char* data);

#endif
