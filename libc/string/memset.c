#include <string.h>


/**
 * Set the first n charactrs of the str to be the the character c.
 * http://www.tutorialspoint.com/c_standard_library/c_function_memset.htm
 */
void* memset(void* str, int c, size_t n){
	unsigned char* str_ = (unsigned char*) str;
    unsigned char c_ = (unsigned char)c;
	for (size_t i = 0; i < n; i++){
		str_[i] = c_;
    }
	return str_;
}

