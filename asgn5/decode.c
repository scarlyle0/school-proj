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

// Main function that decodes encoded text
// Accepts argc and double pointer argv for getopt
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
        // Get header and exit if magic number is different
        Header h = { 0, 0, 0, 0 };
        read_bytes(infile, (uint8_t *) &h, sizeof(h));
        if (h.magic != MAGIC) {
            fprintf(stderr, "Error: Invalid magic number.\n");
            exit(EXIT_FAILURE);
        }

        fchmod(outfile, h.permissions);

        // Read dumped tree
        uint8_t tree[h.tree_size];
        read_bytes(infile, tree, h.tree_size);

        // Rebuild tree
        Node *root = rebuild_tree(h.tree_size, tree);

        uint8_t bit = 0;
        uint64_t written_symbols = 0;
        Node *current = root;
        // Go through the codes in infile and rewrite symbols until file_size matches
        // Pseudo from assignment PDF
        while (written_symbols != h.file_size) {
            read_bit(infile, &bit);
            if (bit == 0 && current != NULL) {
                current = current->left;
            } else if (bit == 1 && current != NULL) {
                current = current->right;
            }
            if (current != NULL && current->right == NULL && current->left == NULL) {
                write_bytes(outfile, &current->symbol, 1);
                written_symbols++;
                current = root;
            }
        }
        // Print out statistics if verbose
        if (verbose) {
            struct stat p_buffer;
            fstat(infile, &p_buffer);
            uint64_t infile_size = p_buffer.st_size;
            fprintf(stderr, "Compressed file size: %lu bytes\n", infile_size);
            fprintf(stderr, "Uncompressed file size: %lu bytes\n", h.file_size);
            fprintf(stderr, "Space saving: %.2f%%\n",
                (100 * (1 - (float) infile_size / (float) h.file_size)));
        }
        delete_tree(&root);
    }
    close(infile);
    close(outfile);
    return 0;
}
