#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <i386/ports.h>


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* VGA_MEMORY;

static size_t terminalRow;
static size_t terminalColumn;
static uint8_t terminalColor;
static uint16_t* terminalBuffer;
static uint16_t terminalIndexPort, terminalDataPort;


/**
 * Upper 4 bits describe the background.
 * Lower 4 bits describe the foreground (text color).
 */
static inline uint8_t makeColor(enum vgaColor fg, enum vgaColor bg) {
	return fg | bg << 4;
}


/**
 * Upper 16 bits describe the color.
 * Lower 16 bits are the character.
 */
static inline uint16_t makeVGAEntry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}


/**
 * Move the hardware cursor.
 */
static void kmoveCursor(size_t x, size_t y){
    const size_t i = y * VGA_WIDTH + x;
    outb(terminalIndexPort, 14);
    outb(terminalDataPort, i >> 8);
    outb(terminalIndexPort, 15);
    outb(terminalDataPort, i);
}


/**
 * Place char c with color at (x,y)
 */
static void kputEntryAt(char c, uint8_t color, size_t x, size_t y){
	const size_t i = y * VGA_WIDTH + x;
	terminalBuffer[i] = makeVGAEntry(c, color);
    kmoveCursor(x, y);
}


/**
 * Clear the terminal.
 */
void kclear(){
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = makeColor(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminalBuffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ ) {
		for ( size_t x = 0; x < VGA_WIDTH; x++ ) {
            kputEntryAt(' ', terminalColor, x, y);
		}
	}
}


/**
 * This function should only be called once during kernel setup.
 */
void kinitialize(uint16_t dataPort, uint16_t indexPort, uint32_t vgaStart){
    terminalDataPort = dataPort;
    terminalIndexPort = indexPort;
    VGA_MEMORY = (uint16_t*)vgaStart;
    kclear();
}


/**
 * Print a character with default colors.
 */
void kputchar(char c){
    if (c == '\n'){
        terminalColumn = 0;
        if (++terminalRow >= VGA_HEIGHT){
            terminalRow = 0;
        }
        kmoveCursor(terminalColumn, terminalRow);
    }
	else {
        kputEntryAt(c, terminalColor, terminalColumn, terminalRow);
        if ( ++terminalColumn >= VGA_WIDTH ) {
            terminalColumn = 0;
            if ( ++terminalRow >= VGA_HEIGHT ) {
                terminalRow = 0;
            }
        }
    }
}


/**
 * Print up to n characters of a string with default colors.
 */
void kwrite(const char* data, size_t n){
	for ( size_t i = 0; i < n; i++ )
		kputchar(data[i]);
}


/**
 * Print a string with default colors.
 */
void kwriteString(const char* data){
	kwrite(data, strlen(data));
}

