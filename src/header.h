#pragma once

#define SHIFT_KEY 41
#define SHIFT_KEY2 53
#define BACKSPACE_KEY 13
#define DELETE_KEY 82
char lowercase[] = "!1234567890-=<\tqwertyuiop[]\n_asdfghjkl;'NN\\zxcvbnm,./\0\0\0 ";
char uppercase[] = "!!@#$%^&*()_+<\tQWERTYUIOP{}\n_ASDFGHJKL:\"NN|ZXCVBNM<>?\0\0\0 ";
#pragma region time
    #define PIT_CHANNEL_0 0x40
    #define PIT_CMD_REG    0x43
    #define RTC_PORT_SECONDS 0x70
    #define RTC_PORT_SECONDS_DATA 0x71

    #define PIT_CONTROL_PORT 0x43
    #define PIT_CHANNEL0_PORT 0x40
#pragma endregion time
#pragma region disk
    //Disk
    #define ATA_DATA_PORT 0x1F0
    #define ATA_ERROR_PORT 0x1F1
    #define ATA_SECTOR_COUNT_PORT 0x1F2
    #define ATA_LBA_LOW_PORT 0x1F3
    #define ATA_LBA_MID_PORT 0x1F4
    #define ATA_LBA_HIGH_PORT 0x1F5
    #define ATA_DRIVE_PORT 0x1F6
    #define ATA_STATUS_COMMAND_PORT 0x1F7
    #define ATA_COMMAND_PORT 0x1F7
    // Other ATA commands
    #define ATA_COMMAND_READ 0x20
    #define ATA_COMMAND_WRITE 0x30
    #define ATA_STATUS_BUSY 0x80
    #define ATA_STATUS_READY 0x40
    #define ATA_STATUS_DRQ 0x08
#pragma endregion disk

#include <stdint.h>
#include <stdbool.h>
#include "utils/utils.h"
#include "io/ports.h"
#include "std.c"