#ifndef OS_INTERRUPTS_HANDLERS
#define OS_INTERRUPTS_HANDLERS

#define DIVISION_BY_ZERO    0x0
#define OVERFLOW            0x4
#define DOUBLE_FAULT        0x8
#define SEGMENTATION_FAULT  0x0C
#define PROTECTION_FAULT    0x0D

#define PRINT               0x30

struct interruptFrame;

namespace handlers {
//    Stub interrupt. Doesn't do anything. Necessary for idt to load correctly
    __attribute__((interrupt)) void stub(interruptFrame *frame) { }

//    User interrupts
    __attribute__((interrupt)) void print(interruptFrame *frame) {
        globalOutputManager->log("PRINT FUNCTION");
    }

//    Exceptions && Errors
    __attribute__((interrupt)) void divisionByZero(interruptFrame *frame) {
        globalOutputManager->error("DIVISION BY ZERO");
    };

    __attribute__((interrupt)) void overflow(interruptFrame *frame) {
        globalOutputManager->error("OVERFLOW");
    };

    __attribute__((interrupt)) void doubleFault(interruptFrame *frame) {
        globalOutputManager->error("DOUBLE FAULT");
    };

    __attribute__((interrupt)) void segmentationFault(interruptFrame *frame) {
        globalOutputManager->error("SEGMENTATION FAULT");
    };

    __attribute__((interrupt)) void protectionFault(interruptFrame *frame) {
        globalOutputManager->error("PROTECTION FAULT");
    };
}

#endif