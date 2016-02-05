#include <i386/ports.h>
#include <i386/pic.h>

uint16_t masterPIC, slavePIC;


void picInit(uint16_t pic1, uint16_t pic2){
    masterPIC = pic1;
    slavePIC = pic2;

    uint16_t data1 = pic1 + 1;
    uint16_t data2 = pic2 + 1;

    outb(pic1, 0x10 + 0x01);  // Init + ICW4 (Set up Cascade mode)
    outb(pic2, 0x10 + 0x01);

    // After this init, the PICs are expecting three additional pieces
    // of data; Vector offset, Cascade position, and mode.

    outb(data1, 0x20);  // Relocate pic1 to interrupt 0x20
    outb(data2, 0x28);  // Relocate pic2 to interrupt 0x28

    outb(data1, 4);     // Tell Master it has Slave on line 2 (00000100)
    outb(data2, 2);     // Tell the Slave it's cascading      (00000010)

    outb(data1, 1);     // Tell the Pic it's in 8086 mode
    outb(data2, 1);

    // At this point, init is complete, and the pic goes into normal
    // Operating mode. But there is still one last thing to do, Set the
    // Interrupt Masks so we don't get interrupts until we set up the
    // Devices on their respective IRQ Lines.

    outb(data1, 0xFF);  // Lines 0-7 are all masked
    outb(data2, 0xFF);  // Lines 8-15 are now masked too.
}
