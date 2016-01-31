#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <i386/ports.h>
#include <drivers/keyboard.h>


/**
 * PS/2 keyboard code.
 * Dependencies:
 * inb function and scancode table.
 */
char getScancode() {
	char c = 0;
	do {
		if (inb(0x60) != c){
			c = inb(0x60);
			if (c > 0)
				return c;
		}
	} while(1);
}

