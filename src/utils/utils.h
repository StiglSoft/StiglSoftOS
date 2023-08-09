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

//Old verision:
//int findInBuffer(uint8_t buff[], uint8_t keyword[], int buffpos){
//    int size0 = sizeof(buff) / sizeof(buff[0]);
//    int size1 = sizeof(keyword) / sizeof(keyword[0]);
//    char out[70];
//    intToHexString(size1,out);
//    write(out);
//    int wordPosition = 0;
//    for(int i =buffpos; i < size0;i++){
//        if(keyword[wordPosition] == buff[i]){
//            wordPosition++;
//            if(wordPosition == size1)return i - wordPosition -1;
//        }else wordPosition =0;
//    }
//    return -1;
//}
int findBytes(const uint8_t haystack[], size_t haystackSize, const uint8_t needle[], size_t needleSize) {
    for (size_t i = 0; i <= haystackSize - needleSize; ++i) {
        size_t j;
        for (j = 0; j < needleSize; ++j) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }   
        if (j == needleSize) {
            return i; 
        }
    }
    return -1;
}
char buffer[64];
void printlnNumber(char description[], int number){
    write(description);
    intToStr(number,buffer);
    write(buffer);
    write("\n");
}
void printlnHex(char description[], int number){
    write(description);
    intToHexString(number,buffer);
    write(buffer);
    write("\n");
}
uint64_t get_tsc() {
    unsigned int lo, hi;
    __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
int cpuFrequency;
int getFrequency(){
     for (int i = 0; i < 100000; ++i) {
        __asm__ volatile("nop");
    }
    uint64_t start = get_tsc();
    for (int i = 0; i < 1000000; ++i) {
        __asm__ volatile("nop");
    }
    uint64_t end = get_tsc();
    uint64_t cycles_elapsed = end - start;
    return (int)((int)cycles_elapsed / 1000000.0);   
}
