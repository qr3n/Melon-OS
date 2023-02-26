#include <cstdint>

unsigned char port_byte_in (unsigned short port);
void port_byte_out (unsigned short port, unsigned char data);

uint16_t port_word_in (uint16_t port);