/*********************************************************************************
* Sean Carlyle, scarlyle
* 2022 Winter CSE101 PA4
* List.h
* Header for the List ADT
*********************************************************************************/

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include <stdbool.h>
#include <stdio.h>

typedef struct ListObj* List;

List newList(void);

void freeList(List* pL);

bool isEmpty(List L);

int length(List L);

int index(List L);

void* front(List L);

void* back(List L);

void* get(List L);

bool listEquals(List A, List B);

void clear(List L);

void set(List L, void* x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, void* x);

void append(List L, void* x);

void insertBefore(List L, void* x);

void insertAfter(List L, void* x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

void printList(FILE* out, List L);

List copyList(List L);

List concatList(List A, List B);

#endif
