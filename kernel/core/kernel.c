#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/vga.h>
#include <drivers/keyboard.h>

/**
 * Core kernel initialization
 */
void ksetup(){
    //vgaInit(0x3D5, 0x3D4, 0xB8000);
	kinitialize();
}


/**
 * At this point, the kernel should be fully set up.
 */
void kmain(void){
	printf("Hello, kernel World!\n");

	while (1){
		printf("%c\n", getScancode());
    }
}
