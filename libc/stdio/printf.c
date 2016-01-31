#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


/**
 * Print the first n characters of a string.
 */
static void print(const char* s, size_t n){
    for (size_t i = 0; i < n; i++){
        putchar((int) s[i]);
    }
}


/**
 * Standard printf function.
 * http://www.tutorialspoint.com/c_standard_library/c_function_printf.htm
 *
 * SUPPORTED TYPES (FOR NOW).
 * NOT ALL OF THE FORMATS ARE YET INCLUDED.
 * THIS IS SUBJECT TO CHANGE.
 * specifiers: c, s
 */
int printf(const char *format, ...){
    va_list parameters;
    va_start(parameters, format);

    int written = 0;
    while (*format != '\0'){
        if (*format == '%'){
            // Found potential specifier
            format++;

            if (*format == 'c'){
                // char
                char c = (char) va_arg(parameters, int);  // Accept ints for chars also
                print(&c, sizeof(c));
            }
            else if (*format == 's'){
                // string
                const char *s = va_arg(parameters, const char*);
                print(s, strlen(s));
            }
            else {
                // ¯\_(ツ)_/¯
                // Found unknown specifier.
                return -1;
            }

            format++;
        }
        else {
            // Some regular character
            // Track how many characters until the next
            // % then advance that many after printing.
            unsigned int amount = 1;
            while (format[amount] != '\0'){
                amount++;
            }
            print(format, amount);
            format += amount;
            written += amount;
        }
    }

    return written;
}
