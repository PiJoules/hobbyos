#include <i386/interrupt.h>


void_callback_arg_t interruptHandlers[256];


/***********************************************************************
* Void_Callback_Arg_t is a function callback with the following format
* void fucntion(unsigned int a, ...);
* x86 calls the functions with the seven General Purpose Registers.
* Arguments: _n = number of interrupt to register
*            _f = function of type void_callback_arg_t
***********************************************************************/
void interruptHandlerRegister(uint8_t _n, void_callback_arg_t _f){
    interruptHandlers[_n] = _f;     // Set function into the vector
}
