#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "hvb:i:n:d:s:"

// This function generates private and public keys
// Writes them to pvfile and pbfile
// Accepts int arg and char **argv
// Returns 0 on success
// Based on description from Assignment PDF
int main(int argc, char **argv) {
    FILE *pbfile;
    FILE *pvfile;
    uint32_t iters = 50;
    uint32_t min_bits = 256;
    uint32_t seed = time(NULL);
    bool verbose = false;
    bool help = false;
    bool pb_on = false;
    bool pv_on = false;
    int opt = 0;
    // Parse command lines
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'b': min_bits = atoi(optarg); break;
        case 'i': iters = atoi(optarg); break;
        case 'n':
            pb_on = true;
            pbfile = fopen(optarg, "w");
            if (pbfile == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            pv_on = true;
            pvfile = fopen(optarg, "w");
            if (pvfile == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 's': seed = atoi(optarg); break;
        }
    }
    if (!pb_on) {
        pbfile = fopen("rsa.pub", "w");
        if (pbfile == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
    }
    if (!pv_on) {
        pvfile = fopen("rsa.priv", "w");
        if (pvfile == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
    }
    // Print help message
    if (help) {
        printf("SYNOPSIS\n   Generates an RSA public/private key pair.\n\nUSAGE\n   ./keygen [-hv] "
               "[-b bits] -n pbfile -d pvfile\n\nOPTIONS\n   -h              Display program help "
               "and usage.\n   -v              Display verbose program output.\n   -b bits         "
               "Minimum bits needed for public key n (default: 256).\n   -i confidence   "
               "Miller-Rabin iterations for testing primes (default: 50).\n   -n pbfile       "
               "Public key file (default: rsa.pub).\n   -d pvfile       Private key file (default: "
               "rsa.priv).\n   -s seed         Random seed for testing.\n");
        fclose(pbfile);
        fclose(pvfile);
        return 0;
    }

    // Set private key file permissions to 0600
    uint32_t fd = fileno(pvfile);
    fchmod(fd, 0600);
    randstate_init(seed);

    mpz_t p_prime, q_prime, n_product, exponent, d_inverse, user, sign;
    mpz_inits(p_prime, q_prime, n_product, exponent, d_inverse, user, sign, NULL);

    // Make keys
    rsa_make_pub(p_prime, q_prime, n_product, exponent, min_bits, iters);
    rsa_make_priv(d_inverse, exponent, p_prime, q_prime);

    // Get username and sign
    mpz_set_str(user, getenv("USER"), 62);
    rsa_sign(sign, user, d_inverse, n_product);

    // Write the keys to both files
    rsa_write_pub(n_product, exponent, sign, getenv("USER"), pbfile);
    rsa_write_priv(n_product, d_inverse, pvfile);

    if (verbose) {
        printf("user = %s\n", getenv("USER"));
        printf("s (%zu bits) = ", mpz_sizeinbase(sign, 2));
        gmp_printf("%Zd\n", sign);
        printf("p (%zu bits) = ", mpz_sizeinbase(p_prime, 2));
        gmp_printf("%Zd\n", p_prime);
        printf("q (%zu bits) = ", mpz_sizeinbase(q_prime, 2));
        gmp_printf("%Zd\n", q_prime);
        printf("n (%zu bits) = ", mpz_sizeinbase(n_product, 2));
        gmp_printf("%Zd\n", n_product);
        printf("e (%zu bits) = ", mpz_sizeinbase(exponent, 2));
        gmp_printf("%Zd\n", exponent);
        printf("d (%zu bits) = ", mpz_sizeinbase(exponent, 2));
        gmp_printf("%Zd\n", d_inverse);
    }

    fclose(pbfile);
    fclose(pvfile);
    mpz_clears(p_prime, q_prime, n_product, exponent, d_inverse, user, sign, NULL);
    randstate_clear();
}
