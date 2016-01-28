#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <drivers/keyboard.h>

void kernel_early(void){
	terminal_initialize();
}

void kernel_main(void){
	printf("Hello, kernel World!\n");
	while (1)
		printf("%c\n", getScancode());
}
