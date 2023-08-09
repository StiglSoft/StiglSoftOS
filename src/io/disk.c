#include "../header.h"
// Buffer to hold the data read from the disk
uint8_t diskBuffer[512];
uint8_t cdromBuffer[2048];

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
void writeSector(uint32_t sectorNumber) {
    // Wait for the disk to become ready
    while ((inb(ATA_STATUS_COMMAND_PORT) & ATA_STATUS_BUSY) != 0);

    // Select drive (master), LBA mode
    outb(ATA_DRIVE_PORT, 0xE0 | ((sectorNumber >> 24) & 0x0F));
    outb(ATA_SECTOR_COUNT_PORT, 1); // Write one sector

    // Set LBA address
    outb(ATA_LBA_LOW_PORT, (uint8_t)sectorNumber);
    outb(ATA_LBA_MID_PORT, (uint8_t)(sectorNumber >> 8));
    outb(ATA_LBA_HIGH_PORT, (uint8_t)(sectorNumber >> 16));

    // Issue write command
    outb(ATA_COMMAND_PORT, ATA_COMMAND_WRITE);

    // Write data from the buffer to our disk
    for (int i = 0; i < 256; ++i) {
        uint16_t word = (diskBuffer[i * 2 + 1] << 8) | diskBuffer[i * 2];
        outw(ATA_DATA_PORT, word);
    }

    // Wait for the disk to finish writing
    while ((inb(ATA_STATUS_COMMAND_PORT) & ATA_STATUS_BUSY) != 0);
}


void disk_sync() {
    // Wait for the disk to become ready
    while ((inb(ATA_STATUS_COMMAND_PORT) & ATA_STATUS_BUSY) != 0);

    // Wait for the disk to finish any ongoing write operations
    while ((inb(ATA_STATUS_COMMAND_PORT) & ATA_STATUS_DRQ) != 0);
}
#define SECTOR_SIZE         512

// Function to read disk size
uint64_t read_disk_size() {
    // Select the drive (master or slave) and send IDENTIFY DEVICE command
    outb(ATA_DRIVE_PORT, 0xA0);
    outb(ATA_COMMAND_PORT, 0xEC);

    // Read the status register
    uint8_t status = inb(ATA_COMMAND_PORT);

    // Wait for the drive to be ready
    while (status & 0x80) {
        status = inb(ATA_COMMAND_PORT);
    }

    // Read the Identify Device data
    uint16_t data[256];
    for (int i = 0; i < 256; ++i) {
        data[i] = inw(ATA_DATA_PORT);
    }

    // Calculate total sectors
    uint64_t total_sectors = ((uint64_t)data[61] << 48) |
                             ((uint64_t)data[60] << 32) |
                             ((uint64_t)data[101] << 16) |
                             data[100];

    return total_sectors;
}