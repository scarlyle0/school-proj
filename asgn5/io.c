#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include "defines.h"
#include "code.h"
#include "io.h"

static uint8_t buffer[BLOCK];
static uint32_t index = 0;

// This function reads a set amount of bytes to buffer
// Accepts infile descriptor, buffer pointer, and bytes to read
// Returns total amount of bytes read
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    ssize_t bytes_read = 1;
    int read_counter = 0;
    while (read_counter < nbytes && bytes_read != 0) {
        bytes_read = read(infile, buf + read_counter, nbytes);
        read_counter += bytes_read;
    }
    return read_counter;
}

// This function writes a set amount of bytes from buffer
// Accepts outfile descriptor, buffer pointer, and bytes to write
// Returns total amount of bytes written
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    ssize_t bytes_written = 1;
    int write_counter = 0;
    while (write_counter < nbytes && bytes_written != 0) {
        bytes_written = write(outfile, buf + write_counter, nbytes);
        write_counter += bytes_written;
    }
    return write_counter;
}

// This function reads a single bit from the file, itwill read next bit if called again
// Accepts infile descriptor and pointer to a uint8_t named bit
// Returns whether the index has reached the end
// Pseudo from Eugenes section
bool read_bit(int infile, uint8_t *bit) {
    static uint8_t bitbuff[BLOCK];
    ssize_t bytes = 0;
    static uint32_t tracker = 0; // Tracks position in buffer
    static uint32_t end = -1; // Tracks last valid bit

    // If index is at 0 read more bytes from infile
    if (tracker == 0) {
        bytes = read_bytes(infile, bitbuff, BLOCK);
        if (bytes < BLOCK) {
            end = (bytes * 8) + 1;
        }
    }
    // Gets the exact bit from tracker position and returns in *bit
    uint8_t bit_mask = 1 << (tracker % 8);
    bit_mask &= bitbuff[tracker / 8];
    bit_mask >>= (tracker % 8);
    *bit = bit_mask;
    tracker++;
    // Reset tracker if reached end of buffer
    if (tracker == BLOCK * 8) {
        tracker = 0;
    }
    return (tracker != end);
}

// This function writes code to the outfile
// Accepts outfile descriptor and pointer to code
// Returns nothing
// Pseudo from Eugenes section
void write_code(int outfile, Code *c) {
    uint8_t bit_mask;
    // For code size
    // Place bit in correct place in buffer
    for (uint32_t i = 0; i < code_size(c); i++) {
        bit_mask = 1 << (index % 8);
        uint8_t bit = code_get_bit(c, i);
        if (bit == 1) {
            buffer[index / 8] |= bit_mask;
        } else {
            buffer[index / 8] &= ~bit_mask;
        }
        index++;
        // When buffer is full flush it and write
        if (index == BLOCK * 8) {
            flush_codes(outfile);
            index = 0;
        }
    }
}

// This function flushes code form buffer and writes
// Accepts outfile descriptor
// Returns nothing
// Pseudo from Eugenes section
void flush_codes(int outfile) {
    uint32_t counter = 0;
    if (index > 0) {
        if ((index % 8) == 0) {
            counter = (index / 8);
        } else {
            // If end index in middle of byte
            // clear the other half of the byte
            counter = (index / 8) + 1;
            uint32_t clear_bit_index = index % 8;
            uint8_t bit_mask = 255;
            uint8_t bit_mask_mask;
            while (clear_bit_index != 8) {
                bit_mask_mask = 1 << clear_bit_index;
                bit_mask &= ~bit_mask_mask;
                clear_bit_index++;
            }
            buffer[index / 8] &= bit_mask;
        }
        write_bytes(outfile, buffer, counter);
    }
}
