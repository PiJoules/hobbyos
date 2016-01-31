#include <string.h>


/**
 * Copies n characters from memory src to memory dst.
 * http://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
 */
void* memcpy(void* dst, const void* src, size_t n){
	unsigned char* dst_ = (unsigned char*) dst;
	const unsigned char* src_ = (const unsigned char*) src;
	for (size_t i = 0; i < n; i++){
		dst_[i] = src_[i];
    }
	return dst_;
}

