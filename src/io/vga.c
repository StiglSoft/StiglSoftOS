#include <stdint.h>


// Function to write a byte to a specific port
void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}
void Clear(){
    // Clearing the screen
    uint16_t* screenBuffer = (uint16_t*)0xB8000;
    for (uint16_t i = 0; i < 320 * 200; ++i) {
        screenBuffer[i] = 0x0700; // Black background (0x00) and white foreground (0x07)
    }
}   
// Function to set the video mode
void setVideoMode() {
    // Setting the video mode 0x03 (80x25 text mode)
    outb(0x03C4, 0x03);
    outb(0x03C2, 0xE3);
    outb(0x03C2, 0x63);
    Clear();
}

// Function to draw a pixel at the specified coordinates
void drawPixel(uint16_t x, uint16_t y, uint8_t color) {
    uint16_t* screenBuffer = (uint16_t*)0xB8000;
    screenBuffer[y * 80 + x] = (color << 8) | 0x07;
}

// Function to hide the cursor
void hideCursor() {
    outb(0x03D4, 0x0A);
    outb(0x03D5, 0x20);
}
// Entry point of the bootloader
void vga_init() {
    setVideoMode();
    drawPixel(40, 12, 0x00); // Drawing a black pixel at (40, 12)
    drawPixel(41, 12, 0x07); // Drawing a white pixel at (41, 12)
    drawPixel(41, 21, 0x07); // Drawing a white pixel at (41, 12)
    drawPixel(61, 21, 0x07); // Drawing a white pixel at (41, 12)
}