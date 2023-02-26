#include "Programs.h"
#include "../GlobalOutputManager.h"

int Programs::execute(uint32_t program[]) {
    uint32_t *start = &program[0];

    int (*entry)() = (int(*)())start;

    int status = entry();

    if (status == 0)
        globalOutputManager->success("Program returned 0");

    else globalOutputManager->error("Error! Program status if fail!");

    return status;
}