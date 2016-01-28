#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <drivers/keyboard.h>

/**
 * Core kernel initialization
 */
void kernel_early(void){
	terminal_initialize();
}

/**
 * At this point, the kernel should be fully set up.
 */
void kernel_main(void){
	printf("Hello, kernel World!\n");
	while (1)
		printf("%c\n", getScancode());
}
