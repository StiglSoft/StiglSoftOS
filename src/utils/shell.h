#pragma once
#include "../header.h"
char shellBuffer[0xFF];
int shellBufferSize = 0;
int shellRunning = 1;
char parts[][0x30];
int partNumber = 0;
int partSubNumber = 0;
void shellWaitForCommand(){
    shellBufferSize = 0;
    for(int i =0;i < shellBufferSize;i++){
        shellBuffer[i] = '\0';
    }
    int commandIndex = 0;
    bool shiftOn = false;
    write("root@/$");
    while(1){
        int key = WaitForKeyDown() -1;
        char KeyChar;
        if(key == SHIFT_KEY || key == SHIFT_KEY2)
            shiftOn = true;
        else if(key == BACKSPACE_KEY){
            if(shellBufferSize > 0){
                Column--;
                write(" ");
                Column--;
                shellBuffer[--commandIndex] = '\0';
                shellBufferSize--;
            }
        }else{
            if(shiftOn){
                KeyChar = uppercase[key];
            }else KeyChar = lowercase[key];
            shiftOn = false;
            if(KeyChar == '\n')
                return;
            else {
                shellBufferSize++;
                shellBuffer[commandIndex++] = KeyChar;
                putchar(KeyChar);
            }
        }
    }
}
void shellExecuteCommand(){
    partNumber = 0;
    partSubNumber = 0;
    //Splits the string
    for(int i =0; i < shellBufferSize;i++){
        if(shellBuffer[i] == ' '){
            partNumber++;
            partSubNumber = 0;
        }else{
            parts[partNumber][partSubNumber++] = shellBuffer[i];
        }
    }
    //For debug!
    //printlnHex("Hex",shellBufferSize);
    //for(int i =0; i < 0x03;i++){
    //    write("\n");
    //    write("\"");
    //    write(parts[1]);
    //    write("\"");
    //}
    if(strcmp(parts[0],"help") == 0){
        write("Help can be found at: https://github.com/StiglSoft/StiglSoftOS/\n");
    }else if(strcmp(parts[0], "ls") == 0){
        int files = fs_ls();
        printlnNumber("Files: ", files);
    }else if(strcmp(parts[0], "exit") == 0){
        write("Exiting...\n");
        shellRunning = false;
    }else if(strcmp(parts[0], "write") == 0){
        for(int i =0; i < 512;i++){
            diskBuffer[i] = 0x00;
        }
        int file = fs_assign(1);
        int sector = fs_get(file);
        int position = 0;
        while(parts[1][position] != '\0'){
            diskBuffer[position] = parts[1][position];
            position++;
        }
        writeSector(sector);
        disk_sync();
    }else if(strcmp(parts[0],"echo") ==0){
        if(strcmp(parts[1],"file") == 0){
            int location = fs_get(atoi(parts[2]));
            //int size = sizes[location];
            readSector(location);
            for(int i =0; i < 512 && diskBuffer[i] != 0x00;i++){
                putchar(diskBuffer[i]);
            }
        }else{
            write(parts[1]);
        }
        write("\n");
    }else if(strcmp(parts[0],"reset") == 0){
        Reboot();
    }else if(strcmp(parts[0],"exec") == 0){
        execute(atoi(parts[1]));
    }else if(strcmp(parts[0],"exit") == 0){
        return;
    }else{
        write("Invalid command!\n");
    }
    for(int i =0; i < 0x0F;i++){
        for(int j =0; j < 0x30;j++){
            parts[i][j] = '\0';
        }
    }
    for(int i =0; i < sizeof(shellBuffer);i++){
        shellBuffer[i] = '\0';
    }
    shellBufferSize =0;
    partNumber = 0;
    partSubNumber =0;
}
void shell(){
    while (shellRunning){
        shellWaitForCommand();
        write("\n");
        shellExecuteCommand();
    }
}