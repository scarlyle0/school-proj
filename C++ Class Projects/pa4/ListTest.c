/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA4
 * * ListTest.c
 * * Tests the List ADT
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(void){
    List L = newList();
    if (isEmpty(L)){
        printf("working\n");
    }
    int aa = 1;
    int bb = 2;
    int cc = 3;
    int dd = 4;
    int *a = &aa;
    int *b = &bb;
    int *c = &cc;
    int *d = &dd;
    append(L, a);
    append(L, b);
    append(L, c);
    if (length(L) == 3){
        printf("working length\n");
    }
    if (front(L) == a){
        printf("working front\n");
    }
    if (back(L) == c){
        printf("working back\n");
    }
    moveFront(L);
    if (index(L) == 0){
        printf("working index\n");
    }
    if (get(L) == a){
        printf("working movefront\n");
    }
    moveBack(L);
    if (get(L) == c){
        printf("working moveback \n");
    }
    List M = copyList(L);
    if (listEquals(L, M)){
        printf("working copy\n");
    }
    clear(M);
    if (!listEquals(L, M)){
        printf("working clear\n");
    }
    printList(stdout, M);
    moveNext(L);
    movePrev(L);
    prepend(L, d);
    printList(stdout, L);
    moveFront(L);
    deleteFront(L);
    moveFront(L);
    insertAfter(L, d);
    insertBefore(L, d);
    deleteBack(L);
    printList(stdout, L);
    moveFront(L);
    delete(L);
    freeList(&M);
    freeList(&L);
    return 0;
}
