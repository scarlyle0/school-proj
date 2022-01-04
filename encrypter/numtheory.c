#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <math.h>
#include "randstate.h"

// This function finds the GCD between a and b and returns it in d
// Accepts mpz_t d, a, and b
// Returns nothing, result is sent back through d
// Based on Pseudo from Assignment PDF
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t temp, a_temp, b_temp;
    mpz_inits(temp, a_temp, b_temp, NULL);
    mpz_set(a_temp, a);
    mpz_set(b_temp, b);
    // While b != 0
    while (mpz_cmp_ui(b_temp, 0) != 0) {
        mpz_set(temp, b_temp);
        mpz_mod(b_temp, a_temp, b_temp);
        mpz_set(a_temp, temp);
    }
    // Return a value
    mpz_set(d, a_temp);
    mpz_clears(temp, a_temp, b_temp, NULL);
}

// This function finds the inverse of i of a mod n
// Accepts mpz_t i,a,n
// Returns nothing, puts inverse in i
// Based on Pseudo from Assignment PDF
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, r_p, t, t_p, q, temp, mul_temp;
    mpz_inits(r, r_p, t, t_p, q, temp, mul_temp, NULL);

    // r, r' = n, a
    mpz_set(r, n);
    mpz_set(r_p, a);
    // t, t' = 0,1
    mpz_set_ui(t, 0);
    mpz_set_ui(t_p, 1);
    // while r' != 0
    while (mpz_cmp_ui(r_p, 0) != 0) {
        mpz_fdiv_q(q, r, r_p);

        mpz_set(temp, r);
        mpz_set(r, r_p);
        mpz_mul(mul_temp, q, r_p);
        mpz_sub(r_p, temp, mul_temp);

        mpz_set(temp, t);
        mpz_set(t, t_p);
        mpz_mul(mul_temp, q, t_p);
        mpz_sub(t_p, temp, mul_temp);
    }
    // if r > 1
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(i, 0);
        mpz_clears(r, r_p, t, t_p, q, temp, mul_temp, NULL);
        return;
    }
    // if t < 0
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    // Return i as inverse
    mpz_set(i, t);
    mpz_clears(r, r_p, t, t_p, q, temp, mul_temp, NULL);
}

// This function computes a to the power d mod n and returns the result in o
// Accepts four mpz_t to find power mod
// Function returns nothing, but result is sent through mpz_t o
// Based of Pseudo from Assignment PDF
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t temp_exponent, temp_out, p, r;
    mpz_inits(temp_exponent, temp_out, p, r, NULL);
    mpz_set(temp_exponent, exponent);
    // out = 1, p = base
    mpz_set_ui(temp_out, 1);
    mpz_set(p, base);
    // While exponent > 0
    while (mpz_cmp_ui(exponent, 0) > 0) {
        mpz_mod_ui(r, exponent, 2);
        if (mpz_cmp_ui(r, 1) == 0) {
            mpz_mul(temp_out, temp_out, p);
            mpz_mod(temp_out, temp_out, modulus);
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus);
        // floor(exponent / 2)
        mpz_fdiv_q_ui(exponent, exponent, 2);
    }
    // Return solution in out
    mpz_set(exponent, temp_exponent);
    mpz_set(out, temp_out);
    mpz_clears(r, temp_out, p, temp_exponent, NULL);
}

// This function performs miller-rabin to determine if a number is prime
// Accepts mpz_t n and uint64_t iters
// Returns true if prime, false otherwise
// Based off pseudo in Assignment PDF
bool is_prime(mpz_t n, uint64_t iters) {
    // Hardcode numbers 0-3
    if (mpz_cmp_ui(n, 0) == 0 || mpz_cmp_ui(n, 1) == 0) {
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0) {
        return true;
    }
    mpz_t r, s, n_one, mod, rand, y, j, s_one, two;
    mpz_inits(r, s, n_one, mod, rand, y, j, s_one, two, NULL);
    mpz_sub_ui(n_one, n, 1);
    mpz_set(r, n_one);
    mpz_mod_ui(mod, r, 2);
    while (mpz_cmp_ui(mod, 0) == 0) {
        mpz_fdiv_q_ui(r, r, 2);
        mpz_mod_ui(mod, r, 2);
        mpz_add_ui(s, s, 1);
    }
    mpz_sub_ui(s_one, s, 1);
    mpz_set_ui(two, 2);
    // Choose random a from 2 to n - 2
    for (uint32_t i = 1; i < iters; i++) {
        mpz_urandomm(rand, state, n_one);
        while (mpz_cmp_ui(rand, 0) == 0 || mpz_cmp_ui(rand, 1) == 0) {
            mpz_urandomm(rand, state, n_one);
        }
        pow_mod(y, rand, r, n);
        // If y != 1 and y != n - 1
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n_one) != 0) {
            mpz_set_ui(j, 1);
            // while j <= s - 1 and y != n - 1
            while (mpz_cmp(j, s_one) <= 0 && mpz_cmp(y, n_one) != 0) {
                pow_mod(y, y, two, n);
                // If y == 1
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(r, s, n_one, mod, rand, y, j, s_one, two, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            // If y != n - 1
            if (mpz_cmp(y, n_one) != 0) {
                mpz_clears(r, s, n_one, mod, rand, y, j, s_one, two, NULL);
                return false;
            }
        }
    }
    mpz_clears(r, s, n_one, mod, rand, y, j, s_one, two, NULL);
    return true;
}

// Generates a new prime number stored in p
// Can specify iters for miller-rabin and bits in prime
// Accepts mpz_t p, and uint64_t bits, iters
// Returns nothing
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_urandomb(p, state, bits + 1);
    uint32_t counter = 0;
    mpz_t temp_bit;
    mpz_init(temp_bit);
    mpz_set_ui(temp_bit, 1);
    // Compute 2^bits - 1
    while (counter != bits - 1) {
        mpz_mul_ui(temp_bit, temp_bit, 2);
        counter++;
    }
    // If p is less then temp bit, multiply p by it
    // This insures p is above our min bits
    if (mpz_cmp(p, temp_bit) < 0) {
        mpz_mul(p, p, temp_bit);
    }
    // While !prime keep trying to fine a prime
    while (!is_prime(p, iters)) {
        mpz_urandomb(p, state, bits + 1);
        if (mpz_cmp(p, temp_bit) < 0) {
            mpz_mul(p, p, temp_bit);
        }
    }
    mpz_clear(temp_bit);
}
