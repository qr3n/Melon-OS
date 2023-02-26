#ifndef OS_DISK_H
#define OS_DISK_H

#include "../../utils/ports/ports.h"

#define STATUS_BUSY   0x80
#define STATUS_READY  0x40

class Disk {
private:
    void waitBSY();
    void waitDRQ();
public:
    void read(uint32_t* target_address, uint32_t LBA, uint8_t sector_count);
};


#endif //OS_DISK_H
