#include "Disk.h"

void Disk::read(uint32_t* buffer, uint32_t LBA, uint8_t sectors) {
    waitBSY();
    port_byte_out(0x1F6,0xE0 | ((LBA >>24) & 0xF));
    port_byte_out(0x1F2,sectors);
    port_byte_out(0x1F3, (uint8_t) LBA);
    port_byte_out(0x1F4, (uint8_t)(LBA >> 8));
    port_byte_out(0x1F5, (uint8_t)(LBA >> 16));

    port_byte_out(0x1F7,0x20); //Send the read command

    for (int j = 0; j < sectors; j++)
    {
        waitBSY();
        waitDRQ();

        for(int i = 0; i < 256;i++)
            buffer[i] = port_word_in(0x1F0);

        buffer+=256;
    }
}

void Disk::waitDRQ() {
    while(!(port_byte_in(0x1F7)&STATUS_READY));
}

void Disk::waitBSY() {
    while(port_byte_in(0x1F7)&STATUS_BUSY);
}
