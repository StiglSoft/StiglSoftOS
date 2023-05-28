#include "io/vga.c"
#include "io/console.c"
#include "io/keyboard.c"
#include <stdint.h>
#include "std.c"
int upperCased = 0;
void Main(void){
    console_init();
    hideCursor();
    vga_init();
    setcolor(CYAN);
    while (1){        
        if(Row > HEIGHT){
            Row = 0;
            vga_init();
        }
        if(isKeyPressed()){
            uint8_t keyCode = readKeyCode();
            if(keyCode > 127)
                continue;
            //char bfr[5];
            //intToStr(keyCode,bfr,0);
            //write(bfr);
            keyCode--;
            if(keyCode == SHIFT_KEY){
                upperCased=1;
                continue;
            }
            char str[2];
            
            str[0] = keyboardLine0[keyCode];
            if(upperCased == 1){
                str[0] = Upper(str[0]);
                upperCased = 0;
            }
            write(str);
        }
    }
    write("Hello world!\nHey");
    while(1);
}