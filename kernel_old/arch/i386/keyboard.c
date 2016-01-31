#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <drivers/keyboard.h>


/**
 * PS/2 keyboard code.
 * Dependencies:
 * inb function and scancode table.
 */
static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile ( "inb %[port], %[ret]"
                   : [ret] "=a"(ret)   // using symbolic operand names as an example, mainly because they're not used in order
                   : [port] "Nd"(port) );
    return ret;
}


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

char getKeyPressed(){
	return (char)((uint8_t)getScancode() + 126);
}
