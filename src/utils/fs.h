#pragma once
#include "../header.h"

int StartSector, EndSector;
uint8_t fsBuffer[512];
uint8_t fsConversionBuffer[8];
uint8_t fsBegin[8] = {0x53,0x53,0x46,0x53,0x42,0x47,0x4E,0x53};
uint8_t fsEnd[8] =   {0x53,0x53,0x46,0x53,0x45,0x4E,0x44,0x53};

uint8_t fsStartSector[3] = {0x53,0x53,0x3D};
uint8_t fsEndSector[3] = {0x45,0x53,0x3D};

uint8_t fsVersion[7] = {0x56,0x45,0x52,0x3D,0x30,0x30,0x31};
uint8_t fsCnType[6] = {0x43,0x54,0x3D,0x41,0x54,0x41};


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
int FSDetect(){
    int index= 0;
    int size = read_disk_size();
    int selected = 0;
    while(index < size){
        readSector(index);
        if(diskBuffer[0] == 0x53 && diskBuffer[1] == 0x53 && diskBuffer[2] == 0x46){
            selected =1;
            for(int i =-8;i < 8;i++){
                if(diskBuffer[500 + i] != 0x00){
                    i = 9;
                    selected = 0;
                }
            }
            if(selected){
                write("Sector found\n");
                int position = findBytes(diskBuffer,sizeof(diskBuffer),fsStartSector,sizeof(fsStartSector)) + 3;
                int position2 = findBytes(diskBuffer,sizeof(diskBuffer),fsEndSector,sizeof(fsEndSector)) + 3;
                printlnHex("",position);
                StartSector = assemble_int8s_into_int32((uint8_t[]){diskBuffer[position++],diskBuffer[position++],diskBuffer[position++],diskBuffer[position++]});
                printlnHex("Starting sector: ",StartSector);
                EndSector = assemble_int8s_into_int32((uint8_t[]){diskBuffer[position2++],diskBuffer[position2++],diskBuffer[position2++],diskBuffer[position2++]});
                printlnHex("Ending sector: ", EndSector);
                return 0;
            }
        }index++;
    }
    return 1;
}
char buff1[64];
void FSInit(){
    int tmp0 = 0;
    int lastKnown = -1;
    uint32_t size = read_disk_size();
    printlnNumber("Disk size!:",size);
    while(tmp0 < size){
        readSector(tmp0);
        if(!VerifyZeroes(diskBuffer))
            lastKnown = tmp0;
        tmp0++;
    }
    printlnNumber("Free space since:",lastKnown);
    if(lastKnown == -1 || lastKnown == size-1){
        write("Disk is full!\nPress any key to reset...");
        WaitForKeyPress();
        asm volatile("int $0x10");
    }
    int freeSpace = (size - lastKnown) *512 / 1024 / 1024;
    intToStr(freeSpace,buff1);
    write("Free space avilable: ");
    write(buff1);
    write("MB\n");
    write("Press any key to write the filesystem...\n");
    WaitForKeyPress();
    int fsBeginingSector = lastKnown+1;
    int fsEndingSector = size-2;
    CreateFS(0,fsBeginingSector,fsEndingSector);
    copySector(fsBuffer,diskBuffer,0,0);
    writeSector(fsBeginingSector);
    CreateFS(1,0x00,0x00);
    copySector(fsBuffer,diskBuffer,0,0);
    writeSector(fsEndingSector);
    disk_sync();
    write("FILESYSTEM WRITEN!\n");
}