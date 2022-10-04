# Assignment 2 - A Little Slice of pi

This program approximates the value of pi, e and the square root of numbers in different ways

and compares them to the same values given by the math.h library.

## How to build program

Run the following command to build "mathlib-test.c" with Makefile:

make all

make

make mathlib-test

## How to Run

Run the following program with

./mathlib-test OPTIONS

where OPTIONS are:

  -a   Runs all tests.

  -e   Runs e test.

  -b   Runs BBP pi test.

  -m   Runs Madhava pi test.

  -r   Runs Euler pi test.

  -v   Runs Viete pi test.

  -n   Runs Newton square root tests.

  -s   Print verbose statistics.

  -h   Display program synopsis and usage.

## How to clean

Clean the output files and binaries with:

make clean
