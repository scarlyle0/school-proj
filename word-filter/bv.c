#include <stdio.h>
#include <stdlib.h>
#include "bv.h"

// Struct from Assignment PDF
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// This function initializes a bit vector
// Takes parameter as a uint32_t length of bit vector
// Returns bv if successful, NULL otherwise
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        if (bv->vector) {
            return bv;
        }
    }
    free(bv);
    return NULL;
}

// This function deletes a bit vector
// Takes parameters as a double pointer to a bv
// Returns nothing
void bv_delete(BitVector **bv) {
    if (*bv) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
}

// This function returns length of bit vector
// Takes a pointer to bit vector as a parameter
// Returns the length of the bit vector
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

// This function sets a bit at i in the bit vector
// Takes in a pointer to bv and uint32_t index i
// Returns false on failure, true on success
bool bv_set_bit(BitVector *bv, uint32_t i) {
    // Find place to set bit
    uint8_t bit_mask = 1 << (i % 8);
    if (i > bv->length) {
        return false;
    } else {
        // Or with byte of bit mask
        bv->vector[i / 8] |= bit_mask;
        return true;
    }
}

// This function clears a bit at i in the bit vector
// Takes in a pointer to bv and uint32_t index i
// Returns false on failure, true on success
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    // Find place to clear bit
    uint8_t bit_mask = 1 << (i % 8);
    if (i > bv->length) {
        return false;
    } else {
        // & the byte with opposite of bit mask
        bv->vector[i / 8] &= ~bit_mask;
        return true;
    }
}

// This functions gets a bit at the ith index in a bit vector
// Takes in a pointer to bv and a uint32_t index i
// Returns true on success, otherwise failure
bool bv_get_bit(BitVector *bv, uint32_t i) {
    // Find place to get bit
    uint8_t bit_mask = 1 << (i % 8);
    if (i > bv->length) {
        return false;
    } else {
        // And the bit_mask with that bit
        // Send it to the index 0 of bytes place
        bit_mask &= bv->vector[i / 8];
        bit_mask >>= (i % 8);
        if (bit_mask == 1) {
            return true;
        } else {
            return false;
        }
    }
}

// This function prints out the bits of a bit vector
// Prints from largest to smallest, left to right
// Takes in parameters as a pointer to bit vector
// Returns nothing
void bv_print(BitVector *bv) {
    uint8_t bit;
    for (int i = bv->length - 1; i >= 0; i--) {
        if (bv_get_bit(bv, i)) {
            bit = 1;
        } else {
            bit = 0;
        }
        printf("%d", bit);
    }
    printf("\n");
}
