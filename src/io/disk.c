#include "../header.h"
// Buffer to hold the data read from the disk
uint8_t diskBuffer[512];



// Function to read a sector from the disk
void readSector(uint32_t sectorNumber) {
    // Wait for the disk to become ready
    while ((inb(ATA_STATUS_COMMAND_PORT) & ATA_STATUS_BUSY) != 0);

    // Select drive (master), LBA mode
    outb(ATA_DRIVE_PORT, 0xE0 | ((sectorNumber >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT_PORT, 1); // Read one sector

    // Set LBA address
    outb(ATA_LBA_LOW_PORT, (uint8_t)sectorNumber);
    outb(ATA_LBA_MID_PORT, (uint8_t)(sectorNumber >> 8));
    outb(ATA_LBA_HIGH_PORT, (uint8_t)(sectorNumber >> 16));

    // Issue read command
    outb(ATA_STATUS_COMMAND_PORT, ATA_COMMAND_READ);

    // Wait for the disk to become ready
    while ((inb(ATA_STATUS_COMMAND_PORT) & ATA_STATUS_BUSY) != 0);

    // Read data from the data port into our buffer
    for (int i = 0; i < 256; ++i) {
        uint16_t word = inw(ATA_DATA_PORT);
        diskBuffer[i * 2] = word & 0xFF;
        diskBuffer[i * 2 + 1] = (word >> 8) & 0xFF;
    }
}