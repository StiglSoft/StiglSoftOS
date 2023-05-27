#include "io/vga.c"
#include "io/console.c"
#include "io/keyboard.c"
#include <stdint.h>
#include "std.c"
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
            char bfr[5];
            intToStr(keyCode,bfr,0);
            write(bfr);
        }
    }
    write("Hello world!\nHey");
    while(1);
}