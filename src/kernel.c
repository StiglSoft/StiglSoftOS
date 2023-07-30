#include "shell.c"
#include "io/disk.c"
void Main(void){
    console_init();
    readSector(0);
    for(int i =0; i < 512; i++){
        //putchar((char)diskBuffer[i]);
    }
    while(1);
    //shell();    
}