#include <stdlib.h>
#include <gmp.h>
#include <stdbool.h>
#include <unistd.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "hvi:o:n:"

// This function decrypts message from infile
// Accepts int argc, char**argv
// Returns 0 on success
// Based on description from Assignment PDF
int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pvfile;
    bool pv_on = false;
    bool verbose = false;
    bool help = false;
    int opt = 0;
    // Parge command line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'i':
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'n':
            pv_on = true;
            pvfile = fopen(optarg, "r");
            if (pvfile == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (!pv_on) {
        pvfile = fopen("rsa.priv", "r");
        if (pvfile == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
    }
    if (help) {
        printf("SYNOPSIS\n   Decrypts data using RSA decryption.\n   Encrypted data is encrypted "
               "by the encrypt program.\n\nUSAGE\n   ./decrypt [-hv] [-i infile] [-o outfile] -n "
               "privkey\n\nOPTIONS\n   -h              Display program help and usage.\n   -v      "
               "        Display verbose program output.\n   -i infile       Input file of data to "
               "decrypt (default: stdin).\n   -o outfile      Output file for decrypted data "
               "(default: stdout).\n   -n pvfile       Private key file (default: rsa.priv).\n");
        fclose(infile);
        fclose(outfile);
        fclose(pvfile);
        return 0;
    }

    // Read in the private key
    mpz_t n_mod, d_inverse;
    mpz_inits(n_mod, d_inverse, NULL);
    rsa_read_priv(n_mod, d_inverse, pvfile);
    if (verbose) {
        printf("n (%zu bits) = ", mpz_sizeinbase(n_mod, 2));
        gmp_printf("%Zd\n", n_mod);
        printf("d (%zu bits) = ", mpz_sizeinbase(d_inverse, 2));
        gmp_printf("%Zd\n", d_inverse);
    }

    // Decrypt the file
    rsa_decrypt_file(infile, outfile, n_mod, d_inverse);

    mpz_clears(n_mod, d_inverse, NULL);
    fclose(outfile);
    fclose(infile);
    fclose(pvfile);
}
