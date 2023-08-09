#include "../header.h"

volatile uint32_t millisecondCounter =0;


#define PIT_COUNTER0                    0x40
#define PIT_CMD                         0x43
#define CMD_BINARY                      0x00
#define CMD_BCD                         0x01
#define CMD_MODE0                       0x00
#define CMD_MODE1                       0x02
#define CMD_MODE2                       0x04
#define CMD_MODE3                       0x06
#define CMD_MODE4                       0x08
#define CMD_MODE5                       0x0a
#define CMD_RW_LOW                      0x10
#define CMD_RW_HI                       0x20
#define CMD_RW_BOTH                     0x30
#define CMD_COUNTER0                    0x0
#define CMD_COUNTER1                    0x4
#define CMD_COUNTER2                    0x8
#define CMD_READBACK                    0xc
#define PIT_FREQUENCY                   1193182

volatile uint32_t g_pitTicks;
static void timer_init(uint32_t frequency){
    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)( (divisor>>8) & 0xFF );

    outb(0x40, l);
    outb(0x40, h);
}

