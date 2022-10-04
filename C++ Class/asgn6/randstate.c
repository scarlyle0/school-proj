#include <stdint.h>
#include <gmp.h>
#include "randstate.h"

gmp_randstate_t state;

// This function initiatializes the randstate
// Accepts a uint64_t which is the seed
// Returns nothing
void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

// This functions clears the randstate
// Accepts nothing
// Returns nothing
void randstate_clear(void) {
    gmp_randclear(state);
}
