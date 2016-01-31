#ifndef _I386_PORTS_H
#define _I386_PORTS_H

#include <stdint.h>

void outb(uint16_t, uint8_t);
uint8_t inb(uint16_t);

#endif
