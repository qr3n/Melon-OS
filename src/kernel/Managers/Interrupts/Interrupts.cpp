#include "Interrupts.h"
#include "../../utils/ports/ports.h"
#include "../GlobalOutputManager.h"
#include "handlers/handlers.h"


void Interrupts::setPIC() {
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    port_byte_out(0x21, 0x00);
    port_byte_out(0xA1, 0x00);
}

void Interrupts::setEntry(int interruptNumber, void* isr, uint8_t flags) {
    IDT_ENTRY *idtEntry = &idt[interruptNumber];

    idtEntry->offsetLow = (uintptr_t)isr & 0xFFFF;
    idtEntry->codeSegment = 0x08;
    idtEntry->zero = 0;
    idtEntry->flags = flags;
    idtEntry->offsetHigh = ((uintptr_t)isr >> 16) & 0xFFFF;
}

void Interrupts::setBasicHandlers() {
//    Exceptions && Errors
    setEntry(DIVISION_BY_ZERO,  (void*)handlers::divisionByZero,    IDT_TRAP_GATE);
    setEntry(OVERFLOW,          (void*)handlers::overflow,          IDT_TRAP_GATE);
    setEntry(DOUBLE_FAULT,      (void*)handlers::doubleFault,       IDT_TRAP_GATE);
    setEntry(SEGMENTATION_FAULT,(void*)handlers::segmentationFault, IDT_TRAP_GATE);
    setEntry(PROTECTION_FAULT,  (void*)handlers::protectionFault,   IDT_TRAP_GATE);

//    User interrupts
    setEntry(PRINT,             (void*)handlers::print,             IDT_USER_GATE);
}

void Interrupts::setStubHandlers() {
    for (int i = 0; i < 256; ++i) {
        if (idt[i].flags == 0) {
            setEntry(i, (void*)handlers::stub, IDT_TRAP_GATE);
        }
    }
}

void Interrupts::enable() {
    globalOutputManager->info("Trying to set basic interrupts...");

    idtRecord.limit = (uint16_t)(sizeof idt);
    idtRecord.base = (uintptr_t)&idt;

    setBasicHandlers();
    setStubHandlers();
    setPIC();

    asm("lidt %0" : : "memory"(idtRecord));
    asm("sti");

    globalOutputManager->success("Interrupts are enabled");
}