# Assignment 1 - Pass the Pigs

This program plays the game Pass the Pigs.
A game where players roll a pig to get points, first to 100 wins.

It accepts a seed to generate the randomness of pig rolls.

It also accepts from 2-10 players.

## How to Build Program

Run the following command to build "pig" with Makefile:

make all

make

or

$ clang -Wall -Werror -Wextra -Wpedantic -o -pig -pig.c

## How to Run

Run the following command to run pig:

/pig 

## Errors

If a non-integer player input is input by the user, the program will invalidate
that input but will also skip asking for the seed input and make
both the default 2 and 2021 respectively.
