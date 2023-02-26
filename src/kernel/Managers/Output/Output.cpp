#include "Output.h"

Output* globalOutputManager;

//    One symbol represents 2 bytes - the character and its color
void Output::putSymbol(char symbol, char color) {
    vgaBuffer[vgaCursor] = symbol;
    vgaBuffer[vgaCursor + 1] = color;

    vgaCursor += 2;
}

void Output::print(const char* msg, char color) {
    textCursor = 0;

    while(msg[textCursor] != '\0') {
        putSymbol(msg[textCursor], color);
        textCursor++;
    }
    newLine();
}

void Output::newLine() {
    vgaCursor += (BUFFER_WIDTH - textCursor) * 2;
}


// Public

void Output::log(const char *msg) {
    print(msg, WHITE);
}

void Output::info(const char *msg) {
    print(msg, BLUE);
}

void Output::success(const char *msg) {
    print(msg, GREEN);
}

void Output::warning(const char *msg) {
    print(msg, YELLOW);
}


void Output::error(const char *msg) {
    print(msg, RED);
}

void Output::clearScreen() {
    vgaCursor = 0;

    while(vgaCursor < BUFFER_WIDTH * BUFFER_HEIGHT * SYMBOL_SIZE) {
        putSymbol(' ', WHITE);
    }

    vgaCursor = 0;
}


