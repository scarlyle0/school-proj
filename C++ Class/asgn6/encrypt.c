#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#include <stdlib.h>
#include <gmp.h>
#include <stdbool.h>
#include <unistd.h>

#define OPTIONS "hvi:o:n:"

// This function encrypts a message from infile
// Accepts int argc, char **argv
// Returns 0 on success
// Based on description from Assignment PDF
int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pbfile;
    bool pb_on = false;
    bool verbose = false;
    bool help = false;
    int opt = 0;
    // Parse command line
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
            pb_on = true;
            pbfile = fopen(optarg, "r");
            if (pbfile == NULL) {
                fprintf(stderr, "Error opening file\n");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
    if (!pb_on) {
        pbfile = fopen("rsa.pub", "r");
        if (pbfile == NULL) {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }
    }
    if (help) {
        printf("SYNOPSIS\n   Encrypts data using RSA encryption.\n   Encrypted data is decrypted "
               "by the decrypt program.\n\nUSAGE\n   ./encrypt [-hv] [-i infile] [-o outfile] -n "
               "pubkey\n\nOPTIONS\n   -h              Display program help and usage.\n   -v       "
               "       Display verbose program output.\n   -i infile       Input file of data to "
               "encrypt (default: stdin).\n   -o outfile      Output file for encrypted data "
               "(default: stdout).\n   -n pbfile       Public key file (default: rsa.pub).\n");
        fclose(outfile);
        fclose(pbfile);
        fclose(infile);
        return 0;
    }
    // Read in public key
    char username[5000] = { 0 };
    mpz_t n_mod, exponent, sign, user;
    mpz_inits(n_mod, exponent, sign, user, NULL);
    rsa_read_pub(n_mod, exponent, sign, username, pbfile);

    if (verbose) {
        printf("user = %s\n", username);
        printf("s (%zu bits) = ", mpz_sizeinbase(sign, 2));
        gmp_printf("%Zd\n", sign);
        printf("n (%zu bits) = ", mpz_sizeinbase(n_mod, 2));
        gmp_printf("%Zd\n", n_mod);
        printf("e (%zu bits) = ", mpz_sizeinbase(exponent, 2));
        gmp_printf("%Zd\n", exponent);
    }

    // Convert username and verify it
    mpz_set_str(user, username, 62);

    if (!rsa_verify(user, sign, exponent, n_mod)) {
        fprintf(stderr, "Error: invalid key.\n");
        exit(EXIT_FAILURE);
    }

    // Encrypt the file
    rsa_encrypt_file(infile, outfile, n_mod, exponent);

    fclose(infile);
    fclose(outfile);
    fclose(pbfile);
    mpz_clears(n_mod, exponent, sign, user, NULL);
    return 0;
}
