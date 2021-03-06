#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

/**
 * Teletypewriter functions in kernel space.
 */

#include <stddef.h>
#include <stdint.h>

enum vgaColor {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};


void kinitialize(uint16_t dataPort, uint16_t indexPort, uint32_t vgaStart);
void kputchar(char c);
void kwrite(const char* data, size_t size);
void kwriteString(const char* data);
void vgaInit(uint16_t data, uint16_t i, uint32_t base);
void kclear();


#endif
