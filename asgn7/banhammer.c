#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

#include "bf.h"
#include "speck.h"
#include "ht.h"
#include "parser.h"
#include "messages.h"

#define OPTIONS "hst:f:"
#define WORD    "[a-zA-Z0-9_'-]+"

// This function finds banned words
// Accepts int arg and double char pointer argv
// Returns 0 on success, 1 on failure
int main(int argc, char **argv) {
    bool help = false;
    bool stats = false;
    uint32_t hash_size = 65536;
    uint32_t bloom_size = 1048576;
    int opt = 0;
    // Getopt loop
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 's': stats = true; break;
        case 't': hash_size = atoi(optarg); break;
        case 'f': bloom_size = atoi(optarg); break;
        }
    }
    // If help is on print and ignore rest of program
    if (help) {
        printf("SYNOPSIS\n  A word filtering program for the GPRSC.\n  Filters out and reports bad "
               "words parsed from stdin.\n\nUSAGE\n  ./banhammer [-hs] [-t size] [-f "
               "size]\n\nOPTIONS\n  -h           Program usage and help.\n  -s           Print "
               "program statistics.\n  -t size      Specify hash table size (default: 2^16).\n  -f "
               "size      Specify Bloom filter size (default: 2^20).\n");
    } else {
        FILE *badspeak = fopen("badspeak.txt", "r");
        if (badspeak == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
        FILE *newspeak = fopen("newspeak.txt", "r");
        if (badspeak == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
        BloomFilter *bf = bf_create(bloom_size);
        HashTable *ht = ht_create(hash_size);
        char word[1024];
        char old[1024];
        char new[1024];
        // Scan in the badspeak and newspeak files to the bloomfilter/hashtable
        while (fscanf(badspeak, "%s\n", word) != EOF) {
            ht_insert(ht, word, NULL);
            bf_insert(bf, word);
        }
        while (fscanf(newspeak, "%s %s\n", old, new) != EOF) {
            ht_insert(ht, old, new);
            bf_insert(bf, old);
        }
        // From Assignment PDF
        regex_t re;
        if (regcomp(&re, WORD, REG_EXTENDED)) {
            fprintf(stderr, "Failed to compile regex.\n");
            return 1;
        }
        char *nextword = NULL;
        Node *badspeak_list = bst_create();
        Node *oldspeak_list = bst_create();
        // Parse each regex word and make it lowercase
        while ((nextword = next_word(stdin, &re)) != NULL) {
            for (uint32_t i = 0; i < strlen(nextword); i++) {
                nextword[i] = tolower(nextword[i]);
            }
            // Check if word in bloom filter, if it is check if its in hash table
            if (bf_probe(bf, nextword)) {
                Node *n = ht_lookup(ht, nextword);
                if (n) {
                    // If in hashtable add it to either oldspeak or badspeak list
                    if (n->newspeak) {
                        oldspeak_list = bst_insert(oldspeak_list, nextword, n->newspeak);
                    } else {
                        badspeak_list = bst_insert(badspeak_list, nextword, NULL);
                    }
                }
            }
        }
        // Print stats if needed
        if (stats) {
            printf("Average BST size: %f\n", ht_avg_bst_size(ht));
            printf("Average BST height: %f\n", ht_avg_bst_height(ht));
            printf("Average branches traversed: %f\n", (float) branches / (float) lookups);
            printf("Hash table load: %f%%\n", (100 * (float) (ht_count(ht) / (float) ht_size(ht))));
            printf(
                "Bloom filter load: %f%%\n", (100 * (float) (bf_count(bf) / (float) bf_size(bf))));
            // If both list are not empty
        } else if (bst_size(oldspeak_list) != 0 || bst_size(badspeak_list) != 0) {
            if (bst_size(oldspeak_list) == 0) { // Print if there is only badspeak
                printf("%s", badspeak_message);
                bst_print(badspeak_list);
            } else if (bst_size(badspeak_list) == 0) { // Print if there is only newspeak
                printf("%s", goodspeak_message);
                bst_print(oldspeak_list);
            } else { // Print if there are both
                printf("%s", mixspeak_message);
                bst_print(badspeak_list);
                bst_print(oldspeak_list);
            }
        }
        // Free everything
        ht_delete(&ht);
        bf_delete(&bf);
        bst_delete(&badspeak_list);
        bst_delete(&oldspeak_list);
        fclose(newspeak);
        fclose(badspeak);
        clear_words();
        regfree(&re);
    }
    return 0;
}
