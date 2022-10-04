# Assignment 4 - Perambulations of Denver Long

This program prints out the shortest hamiltonian path of 

a graph. A hamiltonian path is one where every vertex is

visited once and the path reaches the first vertex at the end.

It prints out this path along with how many

recursive calls it took, and the path length.

The user can specify whether they want all paths found to

be printed. They can also specify which file to read the graphs

from and where to print the output to. 

## How to build program

Run the following command to build "tsp" with Makefile:

make all

make

make tsp

## How to Run

Run the following program with:

./tsp [-u] [-v] [-h] [-i infile] [-o outfile]

where:

  -u             Use undirected graph.

  -v             Enable verbose printing.

  -h             Program usage and help.

  -i infile      Input containing graph (default: stdin)

  -o outfile     Output of computed path (default: stdout)

## Scan build Warnings

Scan build warns of potential problems but the program still works fine

tsp.c:77:17: warning: Potential leak of memory pointed to by 'cities'
                fprintf(outfile, "Error: malformed edge\n");

It says there is a potential leak in memory, but when we check with valgrind there is no leak
so it is okay.


tsp.c:25:11: warning: Value stored to 'infile' during its initialization is never read
    FILE *infile = stdin;

This is okay because it doesn't really affect our program. It still works and the infile
defaults to stdin, and also changes if we select -i
