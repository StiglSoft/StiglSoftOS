#include "header.h"
#include "stiglsoftvm/executor.c"
#include "io/keyboard.c"
#include "std.c"
int upperCased = 0;

void initShell(){
    hideCursor();
    console_init();
    vga_init();
    Clear();
    setcolor(LIGHT_GREEN);
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

int cmp1(char a[], char b[]){
    int i =0;
    while (a[i] == b[i]);
    if(a[i] == '\0')
        return 1;
    return 0;
}
void shell(){
    int buffer1[512];
    int count =0;
    int cnt = 0;
    initShell();
    while(1){
        int prt = 1;
        char inp = getChar();
        if(inp == '1'){
            buffer1[count] += 1;
        }else if(inp == '2'){
            buffer1[count] += 2;
        }else if(inp == '3'){
            buffer1[count] += 3;
        }else if(inp == '4'){
            buffer1[count] += 4;
        }else if(inp == '5'){
            buffer1[count] += 5;
        }else if(inp == '6'){
            buffer1[count] += 6;
        }else if(inp == '7'){
            buffer1[count] += 7;
        }else if(inp == '8'){
            buffer1[count] += 8;
        }else if(inp == '9'){
            buffer1[count] += 9;
        }else if(inp == '0'){
            buffer1[count] += 0;
        }else if(inp == 'a'){
            buffer1[count] += 10;
        }else if(inp == 'b'){
            buffer1[count] += 11;
        }else if(inp == 'c'){
            buffer1[count] += 12;
        }else if(inp == 'd'){
            buffer1[count] += 13;
        }else if(inp == 'e'){
            buffer1[count] += 14;
        }else if(inp == 'f'){
            buffer1[count] += 15;
        }else if(inp == '!'){
            asm volatile("int $0x10\n");
        }else if(inp == '\n'){
            write("\nCompiling!\n");
            Execute(buffer1,count);
            cnt--;
        }else{
            prt = 0;
            count--;
            cnt--;
        }
        if(prt)
            printCh(inp);
        cnt++;
        if(cnt == 2){
            if(buffer1[count] > 255)
                setcolor(RED);
            count++;
            cnt = 0;
            printCh(' ');
        }else{
            buffer1[count] *= 16;
        }
    }
}