#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <i386/gdt.h>
#include <drivers/keyboard.h>

/**
 * Core kernel initialization
 */
void ksetup(){
	kinitialize(0x3d5, 0x3d4, 0xb8000);
    printf("Initialized the tty.\n");

    gdtInit();
}


/**
 * At this point, the kernel should be fully set up.
 */
void kmain(){
	printf("Hello, kernel World!\n");

    //while (1){
	//	printf("%c\n", getScancode());
    //}
}
