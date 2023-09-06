#pragma once
#include <stdint.h>
struct Stack{
    uint8_t data[0xFF];
    int count;
};
uint8_t stack_pop(struct Stack* stack){
    if(stack->count < 1)
        return 0;
    stack->count--;
    return stack->data[stack->count] = 0;
}
void stack_push(uint8_t value,struct Stack* stack){
    stack->data[
        stack->count
    ] = value;
    stack->count++;
}