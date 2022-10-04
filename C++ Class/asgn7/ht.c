#include "bst.h"
#include "ht.h"
#include "salts.h"
#include "speck.h"

#include <stdlib.h>
#include <stdint.h>

uint64_t lookups;

// From Assignment PDF
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

// This function creates a hash table
// Accepts a uint32_t size
// Returns a pointer to hash table
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->size = size;
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        return ht;
    }
    free(ht);
    return NULL;
}

// This function deletes a hash table
// Accepts a ** to hash table
// Returns nothing
void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t i = 0; i < ht_size(*ht); i++) {
            bst_delete(&(*ht)->trees[i]);
        }
        free((*ht)->trees);
        free(*ht);
        *ht = NULL;
    }
}

// This function returns size of hash table
// Accepts * to hash table
// Returns the size as uint32_t
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// This function looks up a word in hash table
// Accepts * hash table and char * oldspeak
// Returns the * to node if found, else NULL *
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups++;
    Node *n = bst_find(ht->trees[hash(ht->salt, oldspeak) % ht_size(ht)], oldspeak);
    return n;
}

// This function inserts a word into the hash table
// Accepts * hash table, char * oldspeak/newspeak
// Returns nothing
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups++;
    Node *n = bst_insert(ht->trees[hash(ht->salt, oldspeak) % ht_size(ht)], oldspeak, newspeak);
    ht->trees[hash(ht->salt, oldspeak) % ht_size(ht)] = n;
}

// This function counts non NULL trees in the hash table
// Accepts * hash table
// Returns the number of non NULL trees as a uint32_t
uint32_t ht_count(HashTable *ht) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        if (ht->trees[i]) {
            counter++;
        }
    }
    return counter;
}

// Returns the average BST size
// Accepts * hash table
// Returns the average BST size as a double
double ht_avg_bst_size(HashTable *ht) {
    double sizecounter = 0;
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        sizecounter += bst_size(ht->trees[i]);
    }
    double count = ht_count(ht);
    return sizecounter / count;
}

// Returns the average BST height
// Accepts * hash table
// Returns the average BST height as a double
double ht_avg_bst_height(HashTable *ht) {
    double heightcounter = 0;
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        heightcounter += bst_height(ht->trees[i]);
    }
    double count = ht_count(ht);
    return heightcounter / count;
}

// Prints the hash table
// Accepts * hash table
// Returns nothing
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        bst_print(ht->trees[i]);
    }
}
