#include "io/console.c"
#include "std.c"
#include "io/disk.c"
#include "io/vga2.c"
#include "utils/fs.h"
#include "header.h"
#include "io/pit.h"
#include "io/rtc.h"
char strbuffer[0xFF];


void Reboot(){
    //Save disk changes
    disk_sync();
    //Crashes the os
    asm volatile("int $0x10");
}
int GetSeconds(){
    struct RTC_time time;
    get_RTC_time(&time);
    return time.seconds;
}
volatile void Main(void){
    console_init();
    hideCursor();
    cpuFrequency = getFrequency();
    cpuFrequency = getFrequency();
    cpuFrequency = getFrequency();
    while(true){
        //printlnNumber("Seconds:",GetSeconds());
        printCh('a');
        delay_with_frequency(1000);
    }
    //write("Detecting filesystem on your machine...\n");
    //if(FSDetect()){
    //    FSInit();
    //    Reboot();
    //}
    
    return;
}