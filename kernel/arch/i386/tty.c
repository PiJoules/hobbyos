#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;

uint16_t terminalIndexPort, terminalDataPort;

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

static void kputEntryAt(char c, uint8_t color, size_t x, size_t y){
	const size_t i = y * VGA_WIDTH + x;
	terminalBuffer[i] = makeVGAEntry(c, color);
}


void kinitialize(){
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


void kputchar(char c){
	kputEntryAt(c, terminalColor, terminalColumn, terminalRow);
	if ( ++terminalColumn >= VGA_WIDTH ) {
		terminalColumn = 0;
        if ( ++terminalRow >= VGA_HEIGHT ) {
            terminalRow = 0;
        }
	}
}


void kwrite(const char* data, size_t size){
	for ( size_t i = 0; i < size; i++ )
		kputchar(data[i]);
}


void kwriteString(const char* data){
	kwrite(data, strlen(data));
}
