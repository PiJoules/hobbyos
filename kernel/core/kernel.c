#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <kernel/tty.h>
#include <i386/gdt.h>
#include <i386/idt.h>
#include <i386/pic.h>
#include <i386/pit.h>
#include <drivers/keyboard.h>

/**
 * Core kernel initialization
 */
void ksetup(){
	kinitialize(0x3d5, 0x3d4, 0xb8000);
    printf("Initialized the tty.\n");

    gdtInit();
    printf("Initialized the gdt.\n");

    idtInit();
    printf("Initialized the idt.\n");

    picInit(0x20, 0xa0);
    printf("Initialized the PIC.\n");

    pitInit(CLOCKS_PER_SEC);
    printf("Initialized the PIT.\n");
}


/**
 * At this point, the kernel should be fully set up.
 */
void kmain(){
	printf("Hello, kernel World!\n");
    //asm volatile ("int $0x3");
    //asm volatile ("int $0x4");

    while(1){
        ;
    }

    //while (1){
	//	printf("%c\n", getScancode());
    //}
}
