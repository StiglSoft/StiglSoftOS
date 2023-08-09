#pragma once
#include "../header.h"

uint8_t fsBuffer[512];
uint8_t fsConversionBuffer[8];
uint8_t fsBegin[8] = {0x53,0x53,0x46,0x53,0x42,0x47,0x4E,0x53};
uint8_t fsEnd[8] =   {0x53,0x53,0x46,0x53,0x45,0x4E,0x44,0x53};

uint8_t fsStartSector[3] = {0x53,0x53,0x3D};
uint8_t fsEndSector[3] = {0x45,0x53,0x3D};

uint8_t fsVersion[7] = {0x56,0x45,0x52,0x3D,0x30,0x30,0x31};
uint8_t fsCnType[6] = {0x43,0x54,0x3D,0x41,0x54,0x41};

int DetectFS(){

}

void CreateFS(int part, int fsBeginSector, int fsEndingSector){
    for(int i =0; i < 512;i++){
        fsBuffer[i] = 0x00;
    }
    int byteIndex = 0;
    if(part == 0){
        byteIndex += WriteAtPosition(fsBuffer,fsBegin,byteIndex,8);

        byteIndex += WriteAtPosition(fsBuffer,(uint8_t[]){0x00},byteIndex,1);
        byteIndex += WriteAtPosition(fsBuffer,fsStartSector,byteIndex,sizeof(fsStartSector));
        split_int32_into_int8s(fsBeginSector,fsConversionBuffer);
        byteIndex += WriteAtPosition(fsBuffer,fsConversionBuffer,byteIndex,4);

        byteIndex += WriteAtPosition(fsBuffer,(uint8_t[]){0x00},byteIndex,1);
        byteIndex += WriteAtPosition(fsBuffer,fsEndSector,byteIndex,sizeof(fsEndSector));
        split_int32_into_int8s(fsEndingSector,fsConversionBuffer);
        byteIndex += WriteAtPosition(fsBuffer,fsConversionBuffer,byteIndex,4);
    }else{
        byteIndex += WriteAtPosition(fsBuffer,fsEnd,byteIndex,8);
    }
}