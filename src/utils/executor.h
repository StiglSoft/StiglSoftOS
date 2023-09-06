#pragma once
#include "../header.h"
struct Stack stack;
int execute(int file){
    int appOwnership = 0;
    int registers[255];
    int jumpLabels[0x20];
    int compareBoi = 0;
    int _file = fs_get(file);
    int _size = sizes[file];
    int codeSize = _size * 512;
    int codeRunning = 1;
    uint8_t code[codeSize];
    uint32_t i32 =0;
    for(int i =0; i < _size;i++){
        readSector(i + _file);
        copySector(diskBuffer,code,0,i * 512);
    }
    if(code[0] != 0xFF || code[1] != 0x50){
        write("File not executable!\n");
        printlnHex("",code[0]);
        printlnHex("",code[1]);
        return 1;
    }
    uint8_t memory[assemble_int8s_into_int32((uint8_t[]){code[0],code[1],code[2],code[3]})];
    int codeBias = 6;
    int labelsAmount = assemble_int8s_into_int32((uint8_t[]){code[codeBias + 0],code[codeBias + 1],code[codeBias + 2],code[codeBias + 3]});
    int labels[labelsAmount];
    for(int i =0; i < labelsAmount;i++){
        codeBias += 4;
        labels[i] = assemble_int8s_into_int32((uint8_t[]){code[codeBias + 0],code[codeBias + 1],code[codeBias + 2],code[codeBias + 3]});
    }codeBias += 4;
    int index = 0;
    while(index + codeBias < codeSize){
        printlnHex("Index:",index);
        if(!codeRunning){
            if(code[index] == 0x10)
                codeRunning = 1;
            continue;
        }
        switch (code[index++]){
            case 0x00:
                break;
            case 0x01:
                //Hardware option
                switch (code[index++]){
                    case 0:
                        uint8_t vga_command = code[index++];
                             if(vga_command == 0x00)vga_init();
                        else if(vga_command == 0x01){
                            unsigned char *VGA = (unsigned char*) VGA_ADDRESS;
                            VGA[code[index++] = code[index++]] * code[index++];
                        }else{
                            vga_clear_screen();
                        }
                    case 1:
                        uint8_t time_command = code[index++];
                             if(time_command == 0x00)time_init();
                        else if(time_command == 0x01)time_delay(code[index++]);
                        break;
                    case 2:
                        uint8_t port_command = code[index++];
                        uint8_t port_arg1 = code[index++];
                        uint8_t port_arg2 = code[index++];
                             if(port_command == 0x00)memory[port_arg2] = inb(port_arg1);
                        else if(port_command == 0x01)outb(port_arg1,memory[port_arg2]);
                        break;
                    case 3:
                        uint8_t console_command = code[index++];
                             if(console_command == 0x00)console_setup();
                        else if(console_command == 0x01)putchar(memory[code[index++]]);
                        else if(console_command == 0x02)Clear();
                        else if(console_command == 0x03){
                            Column = memory[code[index++]];
                            Row = memory[code[index++]];
                        }
                        break;
                    case 4:
                        uint8_t keyboard_command = code[index++];
                        uint8_t keyboard_arg1 = code[index++];
                        uint8_t keyboard_arg2 = code[index++];
                        int key = 0;
                        if(keyboard_command == 0x00){
                            key = WaitForKeyDown();
                        }else if(keyboard_command == 0x01){
                            key = WaitForKeyPress();
                        }else{
                            while(!isKeyPressed())
                            key = readKeyCode();
                        }
                        if(keyboard_arg1 == 0x00)
                            memory[keyboard_arg2] = key;
                        else memory[keyboard_arg2] = lowercase[key];
                        break;
                    case 5:
                        struct RTC_time time;
                        get_RTC_time(&time);
                        uint8_t rtc_arg1 = code[index++];
                        memory[rtc_arg1++] = time.seconds;
                        memory[rtc_arg1++] = time.minutes;
                        memory[rtc_arg1++] = time.hours;
                        break;
                }
                break;
            case 0x02:
                uint8_t app_command = code[index++];
                if(app_command == 0x01)
                    execute(file);
                else if(app_command == 0x02)
                    if(appOwnership == 0)
                        return 0;
                    else write("App can't quit when holding ownership!\n");
                else if(app_command == 0x03){
                    appOwnership = code[index++];
                    write("Ownership has changed!\n");
                }else if(app_command == 0x04){
                    if(appOwnership == 0)
                        shell();
                    else write("App can't stop when holding ownership!\n");
                break;
            case 0x03:
                uint8_t kern_command = code[index++];
                if(kern_command == 0x01)
                    if(appOwnership == 0)
                        Reboot();
                    else write("App can't reboot the kernel when holding ownership!\n");
                break;
            case 0x04:
                uint8_t mov_arg0 = code[index++];
                uint8_t mov_arg1 = code[index++];
                memory[mov_arg0] = memory[mov_arg1];
                break;
            case 0x05:
                uint8_t jmp_arg0 = code[index++];
                index = codeBias + labels[jmp_arg0];
                break;
            case 0x06:
                uint8_t add_arg0 = code[index++];
                uint8_t add_arg1 = code[index++];
                memory[add_arg0] += memory[add_arg1];
                break;
            case 0x07:
                uint8_t sub_arg0 = code[index++];
                uint8_t sub_arg1 = code[index++];
                memory[add_arg0] -= memory[add_arg1];
                break;
            case 0x08:
                uint8_t mul_arg0 = code[index++];
                uint8_t mul_arg1 = code[index++];
                memory[mul_arg0] *= memory[mul_arg1];
                break;
            case 0x09:
                uint8_t div_arg0 = code[index++];
                uint8_t div_arg1 = code[index++];
                memory[div_arg0] /= memory[div_arg1];
                break;
            case 0x0A:
                memory[code[index++]] = 0;
                break;
            case 0x0B:
                code[index++] = stack_pop(&stack);
                break;
            case 0x0C:
                stack_push(code[index++],&stack);
                break;
            case 0x0E:
                execute(i32);
                break;
            case 0x0F:
                codeRunning = 0;
                break;
            case 0x11:
                i32 = memory[code[index++]];
                break;
            case 0x12:
                index = i32;
                break;
            case 0x13:
                memory[code[index++]] = code[index++];
                break;
        }

    }
    }
}