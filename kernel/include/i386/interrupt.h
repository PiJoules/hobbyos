#ifndef _I386_INTERRUPT_H
#define _I386_INTERRUPT_H

#include <stdint.h>
#include <kernel/callback.h>

void interruptHandlerRegister(uint8_t _n, void_callback_arg_t _f);

#endif
