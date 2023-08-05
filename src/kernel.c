//#include "shell.c"
#include "std.c"
//#include "io/console.c"
//#include "io/disk.c"
//#include "io/keyboard.c"
#include "io/ports.c"
#include "io/vga2.c"


void Main(void){
    vga_test();    
    /*console_init();
    readSector(0);
    int index = 0;
    while(1){
        for(int i =0; i < 64; i++){
            char str[2];
            intToHexString(diskBuffer[index + i],str);
            write(str);
            write("  ");
        }
        Row = 12;
        Column = 0;

        char a[3];
        write("Byte:");
        intToStr(index,a,3);
        write(a);
        while(1){
            if(isKeyPressed()){
                uint8_t keyCode = readKeyCode();
                if(keyCode > 127)
                    break;
            }
        }
        index += 64;
        Clear();
        Row = 0;
        Column = 0;

    }*/
}