#include <stdint.h>
#include "ports.h"

// Function to check if a key is pressed
int isKeyPressed() {
    return (inb(0x64) & 0x01);
}
// Function to read a key code from the keyboard
uint8_t readKeyCode() {
    return inb(0x60);
}

