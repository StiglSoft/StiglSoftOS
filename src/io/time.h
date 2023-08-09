#include "rtc.h"

int speed;
int GetSeconds(){
    struct RTC_time time;
    get_RTC_time(&time);
    return time.seconds;
}

void time_init(){
    int s = GetSeconds();
    while(GetSeconds() == s);
    s++;
    while(1){
        speed++;
        if(GetSeconds() != s)
            break;
    }
    speed/=4;
}
void time_delay(){
    for(int i =0; i < 1000;i++)
        for(int i =0; i < speed;i++){
            asm volatile("nop");
        }
}