#include "code.h"
#include "defines.h"
#include <stdio.h>

// This function initializes the code data structure
// Accepts no parameters
// Returns the initialized code structure
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
    }
    return c;
}

// This function returns the top of the code
// Accepts a code pointer as parameter
// Returns the top of the code
uint32_t code_size(Code *c) {
    return (c->top);
}

// This function shows whether the code is empty
// Accepts a code pointer as parameter
// Returns true if empty, false otherwise
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

// This function shows whether the code is full
// Accepts a code pointer as parameter
// Returns true if full, false otherwise
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    } else {
        return false;
    }
}

// This function sets the ith bit in code to 1
// Accepts a code pointer and a uint i as paremeter
// Returns false if i is out of bounds, otherwise true
bool code_set_bit(Code *c, uint32_t i) {
    uint8_t bit_mask = 1 << (i % 8);
    if (i > 256) {
        return false;
    } else {
        c->bits[i / 8] |= bit_mask;
        return true;
    }
}

// This function sets the ith bit in code to 0
// Accepts a code pointer and a uint i as paremeter
// Returns false if i is out of bounds, otherwise true
bool code_clr_bit(Code *c, uint32_t i) {
    uint8_t bit_mask = 1 << (i % 8);
    if (i > 256) {
        return false;
    } else {
        c->bits[i / 8] &= ~bit_mask;
        return true;
    }
}

// This function gets the ith bit in the code
// Accepts a code pointer and a uint i as paremeter
// Returns false if i is out of bounds, returns true is the bit is 1, else false
bool code_get_bit(Code *c, uint32_t i) {
    uint8_t bit_mask = 1 << (i % 8);
    if (i > 256) {
        return false;
    } else {
        bit_mask &= c->bits[i / 8];
        bit_mask >>= (i % 8);
        if (bit_mask == 1) {
            return true;
        } else {
            return false;
        }
    }
}

// This function pushes a bit to the code
// Accepts a code pointer and a uint bit as parameter
// Returns false if code is full, returns true on success
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    } else {
        uint8_t bit_mask = bit << (c->top % 8);
        c->bits[c->top / 8] |= bit_mask;
        c->top++;
        return true;
    }
}

// This functions pops a bit from the code
// Accepts a code pointer and a uint pointer bit as parameter
// Returns false if code is empty, returns true on success
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    } else {
        *bit = 0;
        c->top--;
        if (code_get_bit(c, c->top)) {
            *bit = 1;
        }
        code_clr_bit(c, c->top);
        return true;
    }
}

// This function prints the code, used for debug
// Accepts a code pointer
// Returns nothing
void code_print(Code *c) {
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        printf("bytes: %u\n", c->bits[i]);
    }
}
