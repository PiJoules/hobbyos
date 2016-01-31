#include <string.h>


/**
 * Copies n characters from src to dst, but for overlapping
 * memory blocks, memmove() is a safer approach than memcpy().
 * http://www.tutorialspoint.com/c_standard_library/c_function_memmove.htm
 */
void* memmove(void* dst, const void* src, size_t n) {
	unsigned char* dst_ = (unsigned char*) dst;
	const unsigned char* src_ = (const unsigned char*) src;
	if ( dst < src ){
		for (size_t i = 0; i < n; i++){
			dst_[i] = src_[i];
        }
    }
	else {
		for (size_t i = n; i > 0; i--) {
			dst_[i-1] = src_[i-1];
        }
    }
	return dst_;
}

