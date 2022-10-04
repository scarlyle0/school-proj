# Assignment 6 - Public Key Cryptopgraphy

This program has three executables: keygen, encrypt, and decrypt.

Keygen creates a public and private key to be used to encrypt/decrypt.

encrypt encrypts a message into ciphertext by using the public key.

decrypt decrypts a message from ciphertext back to normal using private key.

Can specify input/output and private key/public key files for each program

## How to build program

Run the following command to build "encrypt", "decrypt, and "keygen" with Makefile:

make all

make

## How to Run

Run keygen with:

   ./keygen [-hv] [-b bits] -n pbfile -d pvfile

where:

   -h              Display program help and usage.

   -v              Display verbose program output.

   -b bits         Minimum bits needed for public key n (default: 256).

   -i confidence   Miller-Rabin iterations for testing primes (default: 50).

   -n pbfile       Public key file (default: rsa.pub).

   -d pvfile       Private key file (default: rsa.priv).

   -s seed         Random seed for testing.

Run encrypt with:

   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey

where:

   -h              Display program help and usage.

   -v              Display verbose program output.

   -i infile       Input file of data to encrypt (default: stdin).

   -o outfile      Output file for encrypted data (default: stdout).

   -n pbfile       Public key file (default: rsa.pub).

Run decrypt with:

   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey

where:

   -h              Display program help and usage.

   -v              Display verbose program output.

   -i infile       Input file of data to decrypt (default: stdin).

   -o outfile      Output file for decrypted data (default: stdout).

   -n pvfile       Private key file (default: rsa.priv).

