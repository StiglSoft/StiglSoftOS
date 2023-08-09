#include <stdint.h>
#include <stdio.h>
int32_t assemble_int8s_into_int32(int8_t bytes[4]) {
    int32_t byte1 = (int32_t)bytes[0] & 0xFF;
    int32_t byte2 = ((int32_t)bytes[1] & 0xFF) << 8;
    int32_t byte3 = ((int32_t)bytes[2] & 0xFF) << 16;
    int32_t byte4 = ((int32_t)bytes[3] & 0xFF) << 24;

    return byte1 | byte2 | byte3 | byte4;
}

void split_int32_into_int8s(int32_t input, int8_t output[4]) {
    output[0] = (int8_t)(input & 0xFF);
    output[1] = (int8_t)((input >> 8) & 0xFF);
    output[2] = (int8_t)((input >> 16) & 0xFF);
    output[3] = (int8_t)((input >> 24) & 0xFF);
}
int main(){
    uint8_t buff[4];
    for(int i =0xFFFFF; i < 0xFFFFFFFFFFFFFFF;i*=0x0F){
        split_int32_into_int8s(i,buff);
        if(assemble_int8s_into_int32(buff) != i){
            printf("Test failed!");
        }
    }
    printf("Test passed!");
}