#pragma once
#include "../header.h"
#include "../io/keyboard.c"

int32_t assemble_int8s_into_int32(int8_t bytes[4]) {
    int32_t byte1 = (int32_t)bytes[0] & 0xFF;
    int32_t byte2 = ((int32_t)bytes[1] & 0xFF) << 8;
    int32_t byte3 = ((int32_t)bytes[2] & 0xFF) << 16;
    int32_t byte4 = ((int32_t)bytes[3] & 0xFF) << 24;

    return byte1 | byte2 | byte3 | byte4;
}

void split_int32_into_int8s(int32_t input, int8_t output[4]) {
    output[0] = (int8_t)(input & 0xFF);
    output[1] = (int8_t)((input >> 8) & 0xFF);
    output[2] = (int8_t)((input >> 16) & 0xFF);
    output[3] = (int8_t)((input >> 24) & 0xFF);
}
void fillSector(uint8_t diskBuffer[]){
    for(int i =0; i < 512;i++){
        diskBuffer[i] = 0x01;
    }
}
void copySector(uint8_t input[],uint8_t output[], int inputOff, int outputOff){
    for(int i =0; i < 512;i++){
        output[i + outputOff] = input[i + inputOff];
    }
}
int VerifyZeroes(uint8_t diskBuffer[]){
    //Verify if it is boot sector
    //if(diskBuffer[510] == 0x55 && diskBuffer[511] == 0xAA){
    //    return 3;
    //}
    //Verifies if sector is full of zeroes
    for(int i =0; i < 512;i++){
        if(diskBuffer[i] != 0x00)
            return 0;
    }
    return 1;
}
int WriteAtPosition(uint8_t fsBuffer[],uint8_t src[], int position, int lenght){
    for(int i =0; i < lenght;i++){
        fsBuffer[i + position] = src[i];
    }return lenght;
}
uint8_t WaitForKeyPress(){
    while(1){
        if(isKeyPressed()){
            uint8_t keyCode = readKeyCode();
            if(keyCode > 127)
            return keyCode;
        }
    }
}
void hideCursor() {
    outb(0x03D4, 0x0A);
    outb(0x03D5, 0x20);
}
int findInBuffer(uint8_t buff[], uint8_t keyword[]){
    int size0 = sizeof(buff);
    int size1 = sizeof(keyword);
    
}