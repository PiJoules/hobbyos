#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#if defined(__is_myos_kernel)
#include <kernel/tty.h>
#endif

static void print(const char* data, size_t data_length){
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

int printf(const char* restrict format, ...){
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
	bool incomprehensible_conversion = false;

	while ( *format != '\0' ){	
		if (*format != '%' || *(++format) == '%'){
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format;

		if (rejected_bad_specifier){
			incomprehensible_conversion = true;
		}
		else if ( *format == 'c' ){
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		}
		else if ( *format == 's' ){
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		}
		else{		
			incomprehensible_conversion = true;
		}

		if (incomprehensible_conversion){
			rejected_bad_specifier = true;
			format = format_begun_at;

			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}
	}

	va_end(parameters);

	return written;
}

