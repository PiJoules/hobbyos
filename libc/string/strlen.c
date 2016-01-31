#include <string.h>


/**
 * Find the length od a string up to (but not inlcuding)
 * the null terminator.
 * http://www.tutorialspoint.com/c_standard_library/c_function_strlen.htm
 */
size_t strlen(const char* string) {
	size_t result = 0;
	while ( string[result] ){
		result++;
    }
	return result;
}

