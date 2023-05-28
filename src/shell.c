#include "header.h"
#include "io/vga.c"
#include "io/console.c"
#include "io/keyboard.c"
#include "std.c"
int upperCased = 0;

void initShell(){
    hideCursor();
    console_init();
    vga_init();
    Clear();
    setcolor(LIGHT_BLUE);
}

int getKey(){
    while (1)
        if(isKeyPressed()){
            uint8_t keyCode = readKeyCode();
            //KeyUP is ignored
            if(keyCode > 127)
                continue;
            return keyCode-1; 
        }
}
char getChar(){
    int key = getKey();
    char chr = lowercase[key];
    if(key == SHIFT_KEY || key == SHIFT_KEY2){
        upperCased = 1;
        return '\0';
    }
    if(upperCased){
        chr = uppercase[key];
        upperCased = 0;
    }
    return chr;
}
void printCh(char str){
    char toprt[2];
    toprt[0] = str;
    write(toprt);
}
int shell(){
    char buffer[255];
    initShell();
    while(1){
        char inp = getChar();
        strcat(&buffer,inp);
        printCh(inp);
    }
}