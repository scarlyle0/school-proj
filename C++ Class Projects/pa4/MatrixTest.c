/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA4
 * * MatrixTest.c
 * * Tests Matrix ADT
 * *********************************************************************************/

#include "Matrix.h"
#include "List.h"

int main(void){
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);
    
    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 2.0);
    changeEntry(A, 1, 3, 3.0);
    changeEntry(A, 2, 1, 4.0);
    changeEntry(A, 2, 2, 5.0);
    changeEntry(A, 2, 3, 6.0);
    changeEntry(A, 3, 1, 7.0);
 `   changeEntry(A, 3, 2, 8.0);
    changeEntry(A, 3, 3, 9.0);

    changeEntry(B, 1, 1, 1.0);
    changeEntry(B, 1, 3, 1.0);
    changeEntry(B, 3, 1, 1.0);
    changeEntry(B, 3, 2, 1.0);
    changeEntry(B, 3, 3, 1.0);
    printf("Matrix Size: %d\n", size(A));
    fprintf(stdout, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(stdout, A);
    fprintf(stdout, "\n");
    fprintf(stdout, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(stdout, B);
    fprintf(stdout, "\n");

    fprintf(stdout, "(1.5)*A =\n");
    Matrix scalmult = scalarMult(1.5, A);
    printMatrix(stdout, scalmult);
    fprintf(stdout, "\n");

    fprintf(stdout, "A+B =\n");
    Matrix plus = sum(A,B);
    printMatrix(stdout, plus);
    fprintf(stdout, "\n");

    fprintf(stdout, "A+A =\n");
    Matrix plustwo = sum(A,A);
    printMatrix(stdout, plustwo);
    fprintf(stdout, "\n");

    fprintf(stdout, "B-A =\n");
    Matrix sub = diff(B,A);
    printMatrix(stdout, sub);
    fprintf(stdout, "\n");

    fprintf(stdout, "A-A =\n");
    Matrix subtwo = diff(A,A);
    printMatrix(stdout, subtwo);
    fprintf(stdout, "\n");

    fprintf(stdout, "Transpose(A) =\n");
    Matrix pose = transpose(A);
    printMatrix(stdout, pose);
    fprintf(stdout, "\n");

    fprintf(stdout, "A*B =\n");
    Matrix mult = product(A,B);
    printMatrix(stdout, mult);
    fprintf(stdout, "\n");

    fprintf(stdout, "B*B =\n");
    Matrix multtwo = product(B,B);
    printMatrix(stdout, multtwo);
    
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
    return 0;
}
