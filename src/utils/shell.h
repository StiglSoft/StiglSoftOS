#pragma once
#include "../header.h"
void shell(){
    bool shiftOn = false;
    while(1){
        int key = WaitForKeyDown() -1;
        char KeyChar;
        if(key == SHIFT_KEY || key == SHIFT_KEY2)
            shiftOn = true;
        else{
            if(shiftOn){
                KeyChar = uppercase[key];
            }else KeyChar = lowercase[key];
            shiftOn = false;
            if(KeyChar == '\n')
                write("\n");
            else putchar(KeyChar);
            
        }
    }
}