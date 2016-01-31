#include <i386/ports.h>


void outb(uint16_t port, unsigned char data) {
    asm volatile("outb dx, al"
        :                             // Output
        : "d"(port), "a" (data)       // Input
    );
}

uint8_t inb(uint16_t _port) {
    uint8_t data;
    asm volatile("inb al, dx"
        : "=a" (data)                   // Output
        : "d" (_port)                   // Input
    );
    return data;
}
