#include <stdint.h>
uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}
// Function to check if a key is pressed
int isKeyPressed() {
    return (inb(0x64) & 0x01);
}

// Function to read a key code from the keyboard
uint8_t readKeyCode() {
    return inb(0x60);
}
