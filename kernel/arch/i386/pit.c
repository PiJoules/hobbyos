#include <time.h>
#include <stdio.h>
#include <i386/ports.h>
#include <i386/interrupt.h>
#include <i386/pit.h>

uint32_t clockTicks;


void pitCallback(unsigned int _a, ...){
    clockTicks++;
    if(clockTicks % CLOCKS_PER_SEC == 0){
        //printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        printf("Uptime...%d\n", _a);
        //scrWriteHex(clockTicks/CLOCKS_PER_SEC);
    } 
}


void clearIRQMask(int _IRQ) {
    unsigned short port;
    unsigned char mask;

    if(_IRQ < 8) {
        port = 0x21;
    } else {
        port = 0xA1;
        _IRQ -= 8;
    }
    mask = inb(port) & ~(1 << _IRQ);
    outb(port, mask);
}


void pitInit(uint32_t freq){
    asm("cli");
    clockTicks = 0;
    interruptHandlerRegister(0x20, &pitCallback);
    uint32_t divisor = PIT_BASE_FREQ / freq;
    outb(PIT_CMD, PIT_CHANNEL_0 | PIT_LHBYTE | PIT_MODE_2 | PIT_BIN_MODE);
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high= (uint8_t)((divisor >> 8) & 0xFF);
    outb(PIT_DATA_0, low);
    outb(PIT_DATA_0, high);
    clearIRQMask(0); // Enable the line, Start Interrupting the CPU.
    asm("sti");
}
