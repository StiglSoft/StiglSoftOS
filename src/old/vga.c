#include <stdint.h>
#include "ports.c"
// Function to write a byte to a specific port

void Clear(){
    // Clearing the screen
    uint16_t* screenBuffer = (uint16_t*)0xB8000;
    //uint8_t* screenBuffer = (uint8_t*)0xA0000;
    for (uint16_t i = 0; i < 320 * 200; ++i) {
        screenBuffer[i] = 0x0700; // Black background (0x00) and white foreground (0x07)
    }
    //uint8_t* screenBuffer = (uint8_t*)0xA0000;
    //uint16_t bufferSize = 320 * 200;
    //
    //for (uint16_t i = 0; i < bufferSize; i++) {
    //    screenBuffer[i] = 4; // Set each pixel to the color index for red
    //}

}   
// Function to set the video mode
void setVideoMode() {
    //Setting the video mode 0x03 (80x25 text mode)
    outb(0x03C4, 0x03);
    outb(0x03C2, 0xE3);
    outb(0x03C2, 0x63);
    //outw(0x03C4, 0x0100); // Miscellaneous Output Register, set the mode select bit
    //outw(0x03D4, 0x0013); // CRT Controller Register - Vertical Total
    //outw(0x03D4, 0x0E13); // CRT Controller Register - Overflow
    //outw(0x03D4, 0x400E); // CRT Controller Register - Vertical Retrace Start
    //outw(0x03D4, 0xEA00); // CRT Controller Register - Vertical Retrace End
    //outw(0x03D4, 0xAC11); // CRT Controller Register - Vertical Display End
    //outw(0x03D4, 0xDF12); // CRT Controller Register - Offset
    //outw(0x03D4, 0x8C06); // CRT Controller Register - Underline Location
    //outw(0x03D4, 0xDF07); // CRT Controller Register - Vertical Blank Start
    //outw(0x03D4, 0x0E07); // CRT Controller Register - Vertical Blank End
    //outw(0x03D4, 0x0014); // CRT Controller Register - Mode Control
    //outw(0x03D4, 0xE317);
    Clear();
}

// Function to draw a pixel at the specified coordinates

//void drawPixel2(uint16_t x, uint16_t y, uint8_t color) {
//    uint8_t* screenBuffer = (uint8_t*)0xA0000;
//    screenBuffer[y * 320 + x] = color; // Assuming `color` is a valid color index (0 to 255)
//}
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