/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA4
 * * Sparse.c
 * * Creates two matrices and performs many operations on them
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

#define MAX_LEN 300

int main(int argc, char **argv) {
    FILE *in, *out;
    
    if(argc != 3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if (in == NULL){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(1);   
    }

    out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int ANNZ = 0;
    int BNNZ = 0;
    int one = 0;
    int two = 0;
    double three = 0;

    fscanf(in, "%d %d %d", &one, &ANNZ, &BNNZ);
    Matrix A = newMatrix(one);
    Matrix B = newMatrix(one);


    for(int i = 0; i < ANNZ; i++){
        fscanf(in, "%d %d %lf", &one, &two, &three);
        changeEntry(A, one, two, three);
    }
  
    for(int i = 0; i < BNNZ; i++){
        fscanf(in, "%d %d %lf", &one, &two, &three);
        changeEntry(B, one, two, three);
    }
    fprintf(out, "A has %d non-zero entries:\n", ANNZ);
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries:\n", BNNZ);
    printMatrix(out, B);
    fprintf(out, "\n");
    
    fprintf(out, "(1.5)*A =\n");
    Matrix scalmult = scalarMult(1.5, A);
    printMatrix(out, scalmult);
    fprintf(out, "\n");
    
    fprintf(out, "A+B =\n");
    Matrix plus = sum(A,B);
    printMatrix(out, plus);
    fprintf(out, "\n");
    
    fprintf(out, "A+A =\n");
    Matrix plustwo = sum(A,A);
    printMatrix(out, plustwo);
    fprintf(out, "\n");
    
    fprintf(out, "B-A =\n");
    Matrix sub = diff(B,A);
    printMatrix(out, sub);
    fprintf(out, "\n");
    
    fprintf(out, "A-A =\n");
    Matrix subtwo = diff(A,A);
    printMatrix(out, subtwo); 
    fprintf(out, "\n");

    fprintf(out, "Transpose(A) =\n");
    Matrix pose = transpose(A);
    printMatrix(out, pose);
    fprintf(out, "\n");

    fprintf(out, "A*B =\n");
    Matrix mult = product(A,B);
    printMatrix(out, mult);
    fprintf(out, "\n");
    
    fprintf(out, "B*B =\n");
    Matrix multtwo = product(B,B);
    printMatrix(out, multtwo);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalmult);
    freeMatrix(&plus);
    freeMatrix(&plustwo);
    freeMatrix(&sub);
    freeMatrix(&subtwo);
    freeMatrix(&pose);
    freeMatrix(&mult);
    freeMatrix(&multtwo);
    fclose(in);
    fclose(out);     
    return 0;   
} 
