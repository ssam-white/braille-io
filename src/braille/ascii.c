#include <stdint.h>

#include "braille/ascii.h"

const uint8_t braille_ascii[128] = {
    ['a'] = 0x01,
    ['b'] = 0x03,
    ['c'] = 0x09,
    ['d'] = 0x19,
    ['e'] = 0x11,
    ['f'] = 0x0B,
    ['g'] = 0x1B,
    ['h'] = 0x13,
    ['i'] = 0x0A,
    ['j'] = 0x1A,
    ['k'] = 0x05,
    ['l'] = 0x07,
    ['m'] = 0x0D,
    ['n'] = 0x1D,
    ['o'] = 0x15,
    ['p'] = 0x0F,
    ['q'] = 0x1F,
    ['r'] = 0x17,
    ['s'] = 0x0E,
    ['t'] = 0x1E,
    ['u'] = 0x25,
    ['v'] = 0x27,
    ['w'] = 0x3A,
    ['x'] = 0x2D,
    ['y'] = 0x3D,
    ['z'] = 0x35,
    [' '] = 0x00
};

void ascii_to_braille(unsigned char* buf, const char* msg, size_t len) {
    for (size_t i = 0; i < len; i++) {
        char c = msg[i];
        buf[i] = braille_ascii[(unsigned char)c];
    }
}


