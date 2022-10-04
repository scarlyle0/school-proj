#include "salts.h"
#include "bf.h"
#include "speck.h"

#include <stdlib.h>

// Struct from Assignment PDF
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// This function creates a bloom filter
// Accepts uint32_t size
// Returns bloomfilter on success, otherwise NULL
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;
        bf->filter = bv_create(size);
        return bf;
    }
    free(bf);
    return NULL;
}

// This function deletes a bloom filter
// Accepts a double pointer to bloom filter
// Returns nothing
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
}

// This function returns size of bloom filter
// Accepts pointer to bloom filter
// Returns size of bloom filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// This function inserts hashed oldspeak into bloom filter
// Accepts oldspeak string and pointer to bloom filter
// Returns nothing
void bf_insert(BloomFilter *bf, char *oldspeak) {
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

// This function checks if hashed oldspeak is in bloom filter
// Accepts oldspeak string and pointer to bloom filter
// Returns true if probably in bloomfilter, false otherwise
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    if (bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
        && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
        && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf))) {
        return true;
    } else {
        return false;
    }
}

// This function returns the number of set bits in a bloom filter
// Accepts pointer to bloom filter
// Returns the number of set bits in a bloom filter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i)) {
            counter++;
        }
    }
    return counter;
}

// This function prints out a bloom filter
// Accepts a pointer to a bloom filter
// Returns nothing
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
