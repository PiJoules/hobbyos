#include <stdio.h>

#if defined(__is_hobbyos_kernel)
#include <kernel/tty.h>
#endif

/**
 * Just write a char to stdout.
 * http://www.tutorialspoint.com/c_standard_library/c_function_putchar.htm
 */
int putchar(int ic){
#if defined(__is_hobbyos_kernel)
	char c = (char) ic;
	kwrite(&c, sizeof(c));
#else
	// TODO: You need to implement a write system call.
#endif
	return ic;
}
