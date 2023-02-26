#ifndef OS_OUTPUT_H
#define OS_OUTPUT_H

#define BUFFER_WIDTH    80
#define BUFFER_HEIGHT   24
#define SYMBOL_SIZE     2

#include "colors.h"

class Output {
private:
    char* vgaBuffer = (char*)0xb8000;

    int textCursor = 0;
    int vgaCursor  = 0;

    void print(const char* msg, char color);
    void newLine();
public:
    void     log(const char* msg);
    void    info(const char* msg);
    void success(const char* msg);
    void warning(const char* msg);
    void   error(const char* msg);

    void clearScreen();
    void putSymbol(char symbol, char color);
};


#endif //OS_OUTPUT_H
