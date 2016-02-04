#include <string.h>
#include <stdio.h>
#include <kernel/callback.h>
#include <i386/ports.h>
#include <i386/idt.h>

extern void idt_flush(unsigned int);

void_callback_arg_t interruptHandlers[256];

struct idt_entry_struct{
    unsigned short base_low;   // The Low 16 bits
    unsigned short selector;   // Segment Selector
    unsigned char always0;    // Always Zero Bytes
    unsigned char flags;      // Flags.
    unsigned short base_high;  // Upper 16 bits of address
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct{
    unsigned short limit;      // How big is it?
    unsigned int base;       // Base entry
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

struct regs {
    unsigned int ds;                                    // DSS
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;// Pusha
    unsigned int int_no, err_code;                      // From our Stub
    unsigned int eip, cs, eflags, useresp, ss;          // Pushed by int
};

/**********************************************************************/
void isr0();     // Differential Pair of interrupts. We use these
void isr1();     // To derive the offset of all the other ones.

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

unsigned short masterPIC, slavePIC;


static void idtSetGate(unsigned char n, unsigned int base, unsigned short selector, unsigned char flags){
    idt[n].base_low = base & 0xFFFF;
    idt[n].base_high= (base >> 16) & 0xFFFF;
    idt[n].selector = selector;
    idt[n].always0  = 0;
    idt[n].flags    = flags;
}


void isrHandler(struct regs *_r){
    void_callback_arg_t handler = interruptHandlers[_r->int_no];
    handler(_r->int_no, _r->err_code, _r->eax, _r->ebx, _r->ecx, _r->edx, _r->edi, _r->esi);
}


void irqHandler(struct regs *_r){
    if (_r->int_no >= 40) {     // Is this from the slave pic?
        outb(slavePIC, 0x20);   // Send Acknowledgement to the Slave
    }
    outb(masterPIC, 0x20);      // Send Acknowledgement to the Master

    void_callback_arg_t handler = interruptHandlers[_r->int_no];
    handler(_r->int_no, _r->err_code, _r->eax, _r->ebx, _r->ecx, _r->edx,
        _r->edi, _r->esi);
}


/***********************************************************************
* Void_Callback_Arg_t is a function callback with the following format
* void fucntion(unsigned int a, ...);
* x86 calls the functions with the seven General Purpose Registers.
* Arguments: _n = number of interrupt to register
*            _f = function of type void_callback_arg_t
***********************************************************************/
void interruptHandlerRegister(unsigned char _n, void_callback_arg_t _f){
    interruptHandlers[_n] = _f;     // Set function into the vector
}

void unhandledInterrupt(unsigned int _intNum, ...){
    //scrWrite("Recieved An Unhandled Interrupt: ");
    //scrWriteHex(_intNum);
    //scrWrite("!\n");
    printf("Received an unhandled interrupt: %c.\n", _intNum);
}


void idtInit(){
    // Get distance between isr stubs.
    unsigned int temp = (unsigned int)isr1 - (unsigned int)isr0;

    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (unsigned int)&idt;
    memset(&idt, 0, sizeof(idt_entry_t)*256);

    // Initialize the Vector Table with the stubs.
    int i;
    for(i = 0; i < 128; i++) {
        idtSetGate(i, (unsigned int)isr0 + (temp*i), 0x08, 0x8E);
    }

    // Initialize the Function calls to default state
    for(i=0; i<256; i++) {
        interruptHandlerRegister(i, unhandledInterrupt);
    }

    idt_flush((unsigned int)&idt_ptr);
}
