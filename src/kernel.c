#include "io/console.c"
#include "std.c"
#include "io/disk.c"
#include "io/vga2.c"
#include "utils/fs.h"
#include "header.h"

char strbuffer[0xFF];
void FSInit(){
    int tmp0 = 0;
    int lastKnown = -1;
    uint32_t size = read_disk_size();
    intToStr(size,strbuffer);
    write("Disk size:");
    write(strbuffer);
    while(tmp0 < size){
        readSector(tmp0);
        if(!VerifyZeroes(diskBuffer))
            lastKnown = tmp0;
        tmp0++;
    }
    intToStr(lastKnown,strbuffer);
    write("\nFree space since:");
    write(strbuffer);write("\n");
    if(lastKnown == -1 || lastKnown == size-1){
        write("Disk is full!\nPress any key to reset...");
        WaitForKeyPress();
        asm volatile("int $0x10");
    }
    int freeSpace = (size - lastKnown) *512 / 1024 / 1024;
    intToStr(freeSpace,strbuffer);
    write("Free space avilable: ");
    write(strbuffer);
    write("MB\n");
    write("Press any key to write the filesystem...\n");
    WaitForKeyPress();
    int fsBeginingSector = lastKnown+1;
    int fsEndingSector = size-2;
    CreateFS(0,fsBeginingSector,fsEndingSector);
    copySector(fsBuffer,diskBuffer,0,0);
    writeSector(fsBeginingSector);
    intToHexString(fsEndingSector,strbuffer);
    write(strbuffer);
    //CreateFS(1,0x00,0x00);
    //copySector(fsBuffer,diskBuffer,0,0);
    //writeSector(fsEndingSector);
    disk_sync();
    write("FILESYSTEM WRITEN!");

}
void Main(void){
    console_init();
    hideCursor();
    FSInit();
    int index= 0;
    int size = read_disk_size();
    int selected = 0;
    while(index < size){
        readSector(index);
        if(diskBuffer[0] == 0x53 && diskBuffer[1] == 0x53 && diskBuffer[2] == 0x46){
            selected =1;
            for(int i =-8;i < 8;i++){
                if(diskBuffer[500 + i] != 0x00){
                    i = 9;
                    selected = 0;
                }
            }
            if(selected){
                write("sector found");
                intToStr(assemble_int8s_into_int32((uint8_t[]){diskBuffer[12],diskBuffer[13],diskBuffer[14],diskBuffer[15]}),strbuffer);
                write(strbuffer);
            }
            
        }index++;
    }
    
}