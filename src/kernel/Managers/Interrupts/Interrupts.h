#ifndef OS_INTERRUPTS_H
#define OS_INTERRUPTS_H


#include <cstdint>

#define IDT_TRAP_GATE         0x8F
#define IDT_USER_GATE         0xEE

struct IDT_ENTRY{
    uint16_t    offsetLow;   // Lower 16bits of isr address
    uint16_t  codeSegment;   // Code segment for this ISR
    uint8_t          zero;   // Set to 0, reserved by intel
    uint8_t         flags;   // Type and attributes; Flags
    uint16_t   offsetHigh;   // Upper 16bits of isr address
} __attribute__ ((packed));

struct IDR_RECORD{
    uint16_t  limit;
    uint32_t   base;
} __attribute__ ((packed));


class Interrupts {
private:
    IDT_ENTRY idt[256];
    IDR_RECORD idtRecord;

    void setEntry(int interruptNumber, void* isr, uint8_t flags);

    void setBasicHandlers();
    void setStubHandlers();
    void setPIC();
public:
    void enable();
};


#endif //OS_INTERRUPTS_H
