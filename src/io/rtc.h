#pragma once
#include "../header.h"

// Function to read a byte from an RTC register
uint8_t read_RTC_register(uint8_t reg) {
    outb(RTC_PORT_SECONDS, reg);
    return inb(RTC_PORT_SECONDS_DATA);
}

// Function to convert BCD to binary
uint8_t bcd_to_binary(uint8_t bcd_value) {
    return (bcd_value >> 4) * 10 + (bcd_value & 0x0F);
}

// Structure to hold time data
struct RTC_time {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
};

// Function to get current time from RTC
void get_RTC_time(struct RTC_time *time) {
    time->seconds = bcd_to_binary(read_RTC_register(0x00)); // Seconds register
    time->minutes = bcd_to_binary(read_RTC_register(0x02)); // Minutes register
    time->hours = bcd_to_binary(read_RTC_register(0x04));   // Hours register
}
