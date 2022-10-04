# Assignment 7 - The Great Firewall of Santa Cruz

This program called banhammer gets input from stdin

and tells you whether words you have used in your

stdin message are in badspeak.txt or newspeak.txt.

It will then print out the words that you used that

were either in badspeak.txt or newspeak.txt along

with their new translation if there is one.

## How to build program

Run one of the following command to build "banhammer" with Makefile:

make all

make

make banhammer

## How to Run

Run banhammer with:

  ./banhammer [-hs] [-t size] [-f size]

where:

  -h           Program usage and help.

  -s           Print program statistics.

  -t size      Specify hash table size (default: 2^16).

  -f size      Specify Bloom filter size (default: 2^20).
