#include "io/console.c"
#include "std.c"
#include "io/disk.c"
#include "io/time.h"
#include "utils/fs.h"
#include "header.h"
#include "utils/shell.h"
#include "utils/executor.h"
#include "io/vga2.c"
#include "utils/triangler.h"
char strbuffer[0xFF];



void Reboot(){
    //Save disk changes
    disk_sync();
    //Crashes the os
    asm volatile("int $0x10");
}

volatile void Main(void){
    run();
    Reboot();
    //Stop
    console_setup();
    write("Console intialized...\n");
    fs_init();
    write("Filesystem intialized...\n");
    time_init();
    write("Timing intialized...\n");
    write("ATA intialized...\n");
    write("Jumping into startup program...\n");
    shell();
    return;
}