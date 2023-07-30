#pragma once
#define SHIFT_KEY 41
#define SHIFT_KEY2 53
char lowercase[] = "!1234567890-=<\tqwertyuiop[]\n_asdfghjkl;'NN\\zxcvbnm,./\0\0\0 ";
char uppercase[] = "!!@#$%^&*()_+<\tQWERTYUIOP{}\n_ASDFGHJKL:\"NN|ZXCVBNM<>?\0\0\0 ";
#include <stdint.h>
#define ATA_DATA_PORT 0x1F0
#define ATA_ERROR_PORT 0x1F1
#define ATA_SECTOR_COUNT_PORT 0x1F2
#define ATA_LBA_LOW_PORT 0x1F3
#define ATA_LBA_MID_PORT 0x1F4
#define ATA_LBA_HIGH_PORT 0x1F5
#define ATA_DRIVE_PORT 0x1F6
#define ATA_STATUS_COMMAND_PORT 0x1F7

// Other ATA commands
#define ATA_COMMAND_READ 0x20
#define ATA_STATUS_BUSY 0x80
#define ATA_STATUS_READY 0x40
#include "io/ports.c"