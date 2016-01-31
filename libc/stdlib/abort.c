#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * Abort the program execution.
 */
__attribute__((noreturn))
void abort(void) {
	printf("Kernel Panic: abort()\n");
	while ( 1 ) { }
	__builtin_unreachable();
}

