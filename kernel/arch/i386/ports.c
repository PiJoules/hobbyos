#include <i386/ports.h>


/**
 * Sends a 8/16/32-bit value on a I/O location.
 * Traditional names are outb, outw and outl respectively.
 */
void outb(uint16_t port, uint8_t data) {
    asm volatile("outb %[data], %[port]"
                 :  // no output
                 : [data] "a"(data), [port] "Nd"(port));  // input
}


/**
 * Receives a 8/16/32-bit value from an I/O location.
 * Traditional names are inb, inw and inl respectively. 
 */
uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %[port], %[ret]"
                 : [ret] "=a"(ret)      // output
                 : [port] "Nd"(port));  // input
    return ret;
}
