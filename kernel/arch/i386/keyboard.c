#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <drivers/keyboard.h>

/**
 * Receives a 8/16/32-bit value from an I/O location.
 * Traditional names are inb, inw and inl respectively. 
 */
static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile ( "inb %[port], %[ret]"
                   : [ret] "=a"(ret)
                   : [port] "Nd"(port) );
    return ret;
}


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

