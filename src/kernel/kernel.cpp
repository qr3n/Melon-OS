// Main kernel file.
// This is where the call is made after switching to protected mode

#include "Managers/GlobalOutputManager.h"

#include "Managers/Output/Output.h"
#include "Managers/Interrupts/Interrupts.h"
#include "Managers/Programs/Programs.h"
#include "Managers/Disk/Disk.h"

// extern "C" is needed for call from assembler, linker expects c-function

extern "C" [[noreturn]] void kernel_main() {
    Output      outputManager;
    Interrupts  interruptsManager;
    Disk        diskManager;
    Programs    programsManager;

    globalOutputManager = &outputManager;

    outputManager.clearScreen();

    outputManager.info   ("Kernel loaded"            );
    outputManager.log    ("Testing log messages"     );
    outputManager.success("Testing success messages" );
    outputManager.warning("Testing warning messages" );
    outputManager.error  ("Testing error messages"   );

    interruptsManager.enable();

    unsigned int program[512]; // Buffer for program (testProgram.asm)

    // Read 1 sector starting from 9
    diskManager.read(&program[0], 0x9, 1);
    programsManager.execute(program);

    while(1);
}