#include "defines.h"
#include "io.h"
#include "node.h"
#include "code.h"
#include "pq.h"
#include "huffman.h"
#include "header.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define OPTIONS "hvi:o:"

// Main function that encodes a file
// Accepts argc and double char pointer argv
// Returns 0
int main(int argc, char **argv) {
    bool verbose = false;
    bool help = false;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile == -1) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        }
    }
    // Print help message
    if (help) {
        fprintf(stderr,
            "SYNOPSIS\n  A Huffman encoder.\n  Compresses a file using the Huffman coding "
            "algorithm.\n\nUSAGE\n  ./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n  -h        "
            "     Program usage and help.\n  -v             Print compression statistics.\n  -i "
            "infile      Input file to compress.\n  -o outfile     Output of compressed data.\n");
    } else {
        // Construct the histogram from the infile
        uint64_t histogram[ALPHABET] = { 0 };
        uint32_t unique_symbols = 2;
        uint8_t buffer[BLOCK];
        histogram[0]++;
        histogram[ALPHABET - 1]++;
        uint32_t num_bytes = BLOCK;
        while (num_bytes == BLOCK) { // Loop through file and add to histogram
            num_bytes = read_bytes(infile, buffer, BLOCK);
            for (uint32_t i = 0; i < num_bytes; i++) {
                if (histogram[buffer[i]] == 0) {
                    unique_symbols++;
                }
                histogram[buffer[i]]++;
            }
        }
        // Build tree form histogram
        Node *root = build_tree(histogram);
        Code table[ALPHABET] = { 0 };
        // Construct code table by taversing huffman tree
        build_codes(root, table);

        // Create a header and write it to outfile
        // Pseudo from Eric section
        struct stat p_buffer;
        fstat(infile, &p_buffer); // Returns info for file in buffer
        fchmod(outfile, p_buffer.st_mode); // Changes outfile permissions to same as infile
        Header h = { 0, 0, 0, 0 };
        h.magic = MAGIC;
        h.permissions = p_buffer.st_mode;
        h.tree_size = (3 * unique_symbols) - 1;
        h.file_size = p_buffer.st_size;
        write_bytes(outfile, (uint8_t *) &h, sizeof(h));

        // Dump tree to outfile
        dump_tree(outfile, root);

        // Write corresponding code of each symbol in infile to outfile
        lseek(infile, 0, SEEK_SET); // Set reader to beginning of file
        num_bytes = BLOCK;
        while (num_bytes == BLOCK) {
            num_bytes = read_bytes(infile, buffer, BLOCK);
            for (uint32_t i = 0; i < num_bytes; i++) {
                write_code(outfile, &table[buffer[i]]);
            }
        }
        flush_codes(outfile); // Make sure buffer is empty
        // Print statistics if verbose
        if (verbose) {
            fstat(outfile, &p_buffer);
            uint64_t outfile_size = p_buffer.st_size;
            fprintf(stderr, "Uncompressed file size: %lu bytes\n", h.file_size);
            fprintf(stderr, "Compressed file size: %lu bytes\n", outfile_size);
            fprintf(stderr, "Space saving: %.2f%%\n",
                (100 * (1 - (float) outfile_size / (float) h.file_size)));
        }
        delete_tree(&root);
    }
    close(infile);
    close(outfile);
    return 0;
}
