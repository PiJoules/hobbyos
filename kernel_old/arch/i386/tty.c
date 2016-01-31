#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;

void kputEntryAt(char, uint8_t, size_t, size_t);

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

void ksetColor(uint8_t color){
	terminalColor = color;
}

void kputEntryAt(char c, uint8_t color, size_t x, size_t y){
	const size_t i = y * VGA_WIDTH + x;
	terminalBuffer[i] = makeVGAEntry(c, color);
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
