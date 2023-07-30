//#include "shell.c"
#include "std.c"
//#include "io/console.c"
#include "io/disk.c"
#include "io/vga_new.c"
void Main(void){
    set_vga_mode();
    clear_screen(0x00);
    for(int i =0; i < 100;i++){
        write_pixel(20,i,0x0F);
    }
    
    //console_init();
    //readSector(1);
    //for(int i =0; i < 512; i++){
    //    char str[2];
    //    //intToHexString(cdromBuffer[i],str);
    //    intToHexString(diskBuffer[i],str);
    //    diskBuffer[i] = 0xAA;
    //    write(str);
    //    write("  ");
    //}
    //writeSector(1);
    //disk_sync();
    while(1);
    //shell();    
}