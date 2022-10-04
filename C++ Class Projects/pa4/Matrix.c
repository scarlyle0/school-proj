/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA4
 * * Matrix.c
 * * Holds the Matrix ADT
*********************************************************************************/

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// entry obj
typedef struct EntryObj* Entry;

typedef struct EntryObj{
    int column;
    double value;
} EntryObj;

// matrix obj
typedef struct MatrixObj{
    int size;
    List *RowArray;
} MatrixObj;

// makes new entry
Entry newEntry(int x, double y){
    Entry E = malloc(sizeof(EntryObj));
    E->column = x;
    E->value = y;
    return E;
}

// frees entry
void freeEntry(Entry* pE){
    if (pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    M->RowArray = malloc((n+1)*sizeof(List));
    for (int i = 1; i < n + 1; i++){
        M->RowArray[i] = newList();
    }
    M->size = n;
    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if (pM != NULL && *pM != NULL){
        for (int i = 1; i < size(*pM)+ 1; i++){
            for(moveFront((*pM)->RowArray[i]); index((*pM)->RowArray[i]) >= 0; moveNext((*pM)->RowArray[i])){
                Entry E = get((*pM)->RowArray[i]);
                freeEntry(&E);
            }
            freeList(&(*pM)->RowArray[i]);
        }
        free((*pM)->RowArray);
        free(*pM);
        *pM = NULL;
    }
}

// // Access functions

// size()
// Return the size of square Matrix M 
int size(Matrix M){
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    int sum = 0;
    for (int i = 1; i < size(M)+ 1; i++){
        if (isEmpty(M->RowArray[i])){
            continue;
        }
        sum += length(M->RowArray[i]);
    }
    return sum;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == B){
        return 1;
    }
    Entry E;
    Entry R;
    if (size(A) != size(B) || NNZ(A) != NNZ(B)){
        return 0;
    }
    for (int i = 1; i < size(A) + 1; i++){
        moveFront(B->RowArray[i]);
        for(moveFront(A->RowArray[i]); index(A->RowArray[i]) >= 0 && index(B->RowArray[i]) >= 0; moveNext(A->RowArray[i])){
             E = get(A->RowArray[i]);
             R = get(B->RowArray[i]);
             if (E->value != R->value){
                 return 0;
             }
             moveNext(B->RowArray[i]);
        }
    }
    return 1;
}


// // Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    for (int i = 1; i < size(M) + 1; i++){
        for(moveFront(M->RowArray[i]); index(M->RowArray[i]) >= 0; moveNext(M->RowArray[i])){
            Entry E = get(M->RowArray[i]);
            freeEntry(&E);
        }
        clear(M->RowArray[i]);
    }   
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (1 <= i && i <= size(M) && 1 <= j && j <= size(M)){
        Entry E = newEntry(j, x);
        Entry R;
        if (x == 0){
            for(moveFront(M->RowArray[i]); index(M->RowArray[i]) >= 0; moveNext(M->RowArray[i])){
                R = get(M->RowArray[i]);
                if (R->column == E->column){
                    freeEntry(&R);
                    delete(M->RowArray[i]);
                    break; 
                }
            }
            freeEntry(&E);
        } else {
            bool hasinsert = false;
            for(moveFront(M->RowArray[i]); index(M->RowArray[i]) >= 0; moveNext(M->RowArray[i])){
                 R = get(M->RowArray[i]);
                 if (R->column == E->column){
                     hasinsert = true;
                     R->value = E->value;
                     freeEntry(&E);
                     break;

                 }
                 if (R->column < E->column){
                     continue; 
                 } else {
                     hasinsert = true;
                     insertBefore(M->RowArray[i], E);
                     break;
                 }
            }
            if (!hasinsert){
                append(M->RowArray[i], E);
            }
        }
    }
}

// // Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    Entry E;
    Matrix M = newMatrix(size(A));
    for (int i = 1; i < size(A) + 1; i++){
        for(moveFront(A->RowArray[i]); index(A->RowArray[i]) >= 0; moveNext(A->RowArray[i])){
            E = get(A->RowArray[i]);
            changeEntry(M, i, E->column, E->value);
        }
    }
    return M;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    Entry E;
    Matrix M = newMatrix(size(A));
    for (int i = 1; i < size(A) + 1; i++){
        for(moveFront(A->RowArray[i]); index(A->RowArray[i]) >= 0; moveNext(A->RowArray[i])){
            E = get(A->RowArray[i]);
            changeEntry(M, E->column, i, E->value);
        }
    }
    return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    Entry E;
    Matrix M = newMatrix(size(A));
    for (int i = 1; i < size(A) + 1; i++){
        for(moveFront(A->RowArray[i]); index(A->RowArray[i]) >= 0; moveNext(A->RowArray[i])){
            E = get(A->RowArray[i]);
            changeEntry(M, i, E->column, x*E->value);
        }
    }
    return M;   
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (size(A) == size(B)){
        if (equals(A,B) == 1){
            Matrix C = scalarMult(2,A);
            return C;
        }
        Entry E;
        Entry R;
        Matrix M = newMatrix(size(A));
        for (int i = 1; i < size(A) + 1; i++){
            moveFront(A->RowArray[i]);
            moveFront(B->RowArray[i]);
            while(index(A->RowArray[i]) >= 0 && index(B->RowArray[i]) >= 0){
                E = get(A->RowArray[i]);
                R = get(B->RowArray[i]);
                if (E->column < R->column){
                    changeEntry(M, i, E->column, E->value);
                    moveNext(A->RowArray[i]);
                } else if (R->column < E->column){
                    changeEntry(M, i, R->column, R->value);
                    moveNext(B->RowArray[i]);
                } else if (E->column == R->column){
                    changeEntry(M, i, E->column, R->value + E->value);
                    moveNext(A->RowArray[i]);
                    moveNext(B->RowArray[i]);
                }
            }
            while(index(A->RowArray[i]) >= 0){
                E = get(A->RowArray[i]);
                changeEntry(M, i, E->column, E->value);
                moveNext(A->RowArray[i]);
            }
            while(index(B->RowArray[i]) >= 0){
                R = get(B->RowArray[i]);
                changeEntry(M, i, R->column, R->value);
                moveNext(B->RowArray[i]);
            }
        }
        return M;
    }
    printf("Matrix sizes are different\n");
    exit(EXIT_FAILURE);
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (size(A) == size(B)){
        Matrix M;
        if (equals(A,B) == 1){
            M = newMatrix(size(A));
            return M;
        }
        Entry E;
        Entry R;
        M = newMatrix(size(A));
        for (int i = 1; i < size(A) + 1; i++){
            moveFront(A->RowArray[i]);
            moveFront(B->RowArray[i]);
            while(index(A->RowArray[i]) >= 0 && index(B->RowArray[i]) >= 0){
                E = get(A->RowArray[i]);
                R = get(B->RowArray[i]);
                if (E->column < R->column){
                    changeEntry(M, i, E->column, E->value);
                    moveNext(A->RowArray[i]);
                } else if (R->column < E->column){
                    changeEntry(M, i, R->column, -R->value);
                    moveNext(B->RowArray[i]);
                } else if (E->column == R->column){
                    changeEntry(M, i, E->column, E->value - R->value);
                    moveNext(A->RowArray[i]);
                    moveNext(B->RowArray[i]);
                }
            }
            while(index(A->RowArray[i]) >= 0){
                E = get(A->RowArray[i]);
                changeEntry(M, i, E->column, E->value);
                moveNext(A->RowArray[i]);
            }
            while(index(B->RowArray[i]) >= 0){
                R = get(B->RowArray[i]);
                changeEntry(M, i, R->column, -R->value);
                moveNext(B->RowArray[i]);
            }
        }
        return M;
    }
    printf("Matrix sizes are different\n");
    exit(EXIT_FAILURE);
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if (size(A) == size(B)){
        Entry E;
        Entry R;
        double sum = 0;
        Matrix T;
        Matrix M = newMatrix(size(A));
        T = transpose(B);
        for (int i = 1; i < size(A) + 1; i++){
            if (isEmpty(A->RowArray[i])){
                continue;
            }
            for (int j = 1; j < size(A) + 1; j++){
                sum = 0;
                moveFront(A->RowArray[i]);
                moveFront(T->RowArray[j]);
                while(index(A->RowArray[i]) >= 0 && index(T->RowArray[j]) >= 0){
                    E = get(A->RowArray[i]);
                    R = get(T->RowArray[j]);
                    if (E->column < R->column){
                        moveNext(A->RowArray[i]);
                    } else if (R->column < E->column){
                        moveNext(T->RowArray[j]);
                    } else if (E->column == R->column){
                        sum += (E->value * R->value);
                        moveNext(A->RowArray[i]);
                        moveNext(T->RowArray[j]);
                    }
                }
                changeEntry(M, i, j, sum);
            }
        }
        freeMatrix(&T);
        return M;
    }
    printf("Matrix sizes are different\n");
    exit(EXIT_FAILURE);
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    Entry E;
    for (int i = 1; i < size(M) + 1; i++){
        if (isEmpty(M->RowArray[i])){
            continue;
        }
        fprintf(out, "%d:", i);
        for(moveFront(M->RowArray[i]); index(M->RowArray[i]) >= 0; moveNext(M->RowArray[i])){
            E = get(M->RowArray[i]);
            fprintf(out," (%d, %0.1f)", E->column, E->value);
        }
        fprintf(out, "\n");
    }
}
