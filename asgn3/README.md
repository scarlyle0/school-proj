# Assignment 3 - Sorting: Putting your affairs in order

This program contains four sorting algorithms that sort random arrays

The user can specify which sort should be used and how many elements

should be printed or used in the array that is sorted. The user can

also set a seed which affects how the arrays values are randomy generated.

the sorting algorithms are shell sort, heap sort, insertion sort, and quick sort.

The output of the program is the sorted array along with how many moves/compares

it took for the sorting algorithm to sort the array.
 
## How to build program

Run the following command to build "sorting" with Makefile:

make all

make

make sorting

## How to Run

Run the following program with:

./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]

where:

   -h              display program help and usage.

   -a              enable all sorts.

   -e              enable Heap Sort.

   -i              enable Insertion Sort.

   -s              enable Shell Sort.

   -q              enable Quick Sort.

   -n length       specify number of array elements (default: 100).

   -p elements     specify number of elements to print (default: 100).

   -r seed         specify random seed (default: 13371453).


## How to clean

Clean the output files and binaries with:

make clean
