#include <stdio.h>

/**
 * Just print a string.
 * http://www.tutorialspoint.com/c_standard_library/c_function_puts.htm
 */
int puts(const char *string){
	return printf("%s\n", string);
}

