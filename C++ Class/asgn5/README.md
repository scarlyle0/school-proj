# Assignment 5 - Huffman Coding

These programs performs Huffman encoding on any file with text in it

this helps space and the program with -v with tell you amount of space

saved. The decoder program will decode encoded files back to their original form.

The decoder will only decode files that have been encoded by the included encoder

program. 


## How to build program

Run the following command to build "encoder" and "decoder" with Makefile:

make all

make

## How to Run
Run the encoder with:

./encode [-h] [-i infile] [-o outfile]

Run the decoder with:

./decode [-h] [-i infile] [-o outfile]

where:

  -h             Program usage and help.

  -v             Print compression statistics.

  -i infile      Input file to compress.

  -o outfile     Output of compressed data.
