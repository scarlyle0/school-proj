#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <math.h>
#include <string.h>
#include "randstate.h"
#include "numtheory.h"

// This functions creates parts of RSA public key
// It creates two primes, their product, and the public exponent
// Accepts mpz_t p,q,n,e to store output and uint64_t nbits and iters
// nbits and iters specify length of prime and iterations of miller-rabin
// Function returns nothing, but places output in mpz_t variables
// Based on description of make_pub from Assignment PDF
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t rand, max, p_temp, q_temp, totient, gcd_v;
    mpz_inits(rand, max, p_temp, q_temp, totient, gcd_v, NULL);
    // Create two primes with bits to p being between nbits/4 and 3*nbits/4
    // With rest of bits going into p
    mpz_set_ui(max, ((3 * nbits) / 4) + 1);
    mpz_urandomm(rand, state, max);
    while (mpz_cmp_ui(rand, nbits / 4) < 0) { // Find random more than nbits/4
        mpz_urandomm(rand, state, max);
    }
    uint64_t p_bits = mpz_get_ui(rand);
    uint64_t q_bits = nbits - p_bits;

    make_prime(p, p_bits, iters);
    make_prime(q, q_bits, iters);

    // Compute totient
    mpz_mul(n, p, q);

    mpz_sub_ui(p_temp, p, 1);
    mpz_sub_ui(q_temp, q, 1);

    mpz_mul(totient, p_temp, q_temp);

    // Find suitable public exponent
    while (mpz_cmp_ui(gcd_v, 1) != 0) {
        mpz_urandomb(rand, state, nbits + 1);
        while (mpz_cmp_ui(rand, nbits - 1) < 0) {
            mpz_urandomb(rand, state, nbits + 1);
        }
        gcd(gcd_v, rand, totient);
    }
    mpz_set(e, rand);

    mpz_clears(rand, max, p_temp, q_temp, totient, gcd_v, NULL);
}

// This function writes a public RSA key to pbfile
// Accepts mpz_t n,e,s, char array and pointer to pbfile
// Returns nothing
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    fprintf(pbfile, "%s\n", username);
}

// This function reads a public RSA key from pbfile
// Accepts mpz_t n,e,s, char array and pointer to pbfile
// Returns nothing
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    char buf[1024];
    fgets(buf, 1024, pbfile);
    gmp_sscanf(buf, "%Zx", n);

    fgets(buf, 1024, pbfile);
    gmp_sscanf(buf, "%Zx", e);

    fgets(buf, 1024, pbfile);
    gmp_sscanf(buf, "%Zx", s);

    fgets(buf, 1024, pbfile);
    buf[strlen(buf) - 1] = '\0';
    sscanf(buf, "%s", username);
}

// This function makes an RSA private key
// Computing d by finding inverse of e mod (p-1)(q-1)
// Accepts mpz_t d,e,p,q
// Returns nothing, puts output in d
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_temp, q_temp;
    mpz_inits(p_temp, q_temp, NULL);

    mpz_set(p_temp, p);
    mpz_set(q_temp, q);
    mpz_sub_ui(p_temp, p_temp, 1);
    mpz_sub_ui(q_temp, q_temp, 1);

    // Compute inverse of e mod (p-1)(q-1)
    mpz_mul(p_temp, p_temp, q_temp);
    mod_inverse(d, e, p_temp);

    mpz_clears(p_temp, q_temp, NULL);
}

// This function writes a private key to pvfile
// Accepts mpz_t n,d and pointer to pvfile
// Returns nothing
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

// This functions read a private key from pvfile
// Accepts mpz_t n,d and pointer to pvfile
// Returns nothing
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    char buf[1024];
    fgets(buf, 1024, pvfile);
    gmp_sscanf(buf, "%Zx", n);
    fgets(buf, 1024, pvfile);
    gmp_sscanf(buf, "%Zx", d);
}

// This function performs RSA encryption and encrypts message m
// Accepts mpz_t c,m,e,n
// Returns nothing, puts encrypted ciphertext in c
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

// This function encrypts contents of infile, writing to outfile
// Accepts pointer to infile, pointer to outfile, mpz_t n,e
// Returns nothing
// Based on description in Assignment PDF
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    uint32_t block_size = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *array = (uint8_t *) calloc(block_size, sizeof(uint8_t));
    array[0] = 255;
    size_t j = block_size - 1;
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    // Read until we do not read an entire block
    while (j == block_size - 1) {
        // Read a block - 1 to account for 0xFF
        j = fread(array + 1, 1, block_size - 1, infile);
        if (j == 0) { // If we ever read 0 return
            mpz_clears(m, c, NULL);
            free(array);
            return;
        }
        mpz_import(m, j + 1, 1, 1, 1, 0, array);
        // Encrypt each block message
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
    }
    mpz_clears(m, c, NULL);
    free(array);
}

// This function performs RSA decryption and decrypts ciphertext
// Accepts mpz_t m,c,d,n
// Returns nothing, decrypted message is put in m
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

// This functions decrypts the contents of infile, writing to outfile
// Accepts pointer to infile and outfile, mpz_t n and d
// Returns nothing
// Based on description from Assignment PDF
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    uint32_t block_size = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *array = (uint8_t *) calloc(block_size, sizeof(uint8_t));
    size_t j = 0;
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    // Continue scanning if haven't found EOF
    while (gmp_fscanf(infile, "%Zx\n", c) != EOF) {
        rsa_decrypt(m, c, d, n);
        mpz_export(array, &j, 1, 1, 1, 0, m);
        // If the array read in is 0, return
        if (strlen((const char *) array) == 0) {
            fprintf(stderr, "Didn't read any numbers.\n");
            mpz_clears(c, m);
            free(array);
            return;
        }
        // Write the decrypted message to outfile
        j = fwrite(array + 1, 1, j - 1, outfile);
    }
    mpz_clears(c, m);
    free(array);
}

// This function performs RSA signing, producing a signature s
// Accepts mpz_t s,m,d,n
// Returns nothing, but puts signature in s
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

// This function performs RSA verification, checking if signature is same
// Accepts mpz_t m,s,e,n
// Returns true if signature is the same, false otherwise
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    } else {
        mpz_clear(t);
        return false;
    }
}
