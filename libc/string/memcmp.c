#include <string.h>


/**
 * Compares the first n bytes of ptr1 and ptr2.
 * http://www.tutorialspoint.com/c_standard_library/c_function_memcmp.htm
 */
int memcmp(const void* ptr1, const void* ptr2, size_t n){
	const unsigned char* a = (const unsigned char*) ptr1;
	const unsigned char* b = (const unsigned char*) ptr2;
	for (size_t i = 0; i < n; i++){
		if ( a[i] < b[i] ){
			return -1;
        }
		else if ( b[i] < a[i] ){
			return 1;
        }
    }
	return 0;
}

