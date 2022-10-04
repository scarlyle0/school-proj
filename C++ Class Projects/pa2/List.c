/*********************************************************************************
* Sean Carlyle, scarlyle
* 2022 Winter CSE101 PA2
* List.c
* Holds the List ADT
*********************************************************************************/

#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   Node next;
   Node previous;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int index;
   int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Creates a new node
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->previous = NULL;
    return(N);
}

// Frees a node
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// Creates a new list
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);   
}

// Frees a List
void freeList(List* pL){
    if (pL != NULL && *pL != NULL){
        while(!isEmpty(*pL)){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// returns whether list is empty
bool isEmpty(List L){
    if(length(L) == 0){
        return true;
    }
    return false;
}

// returns length of list
int length(List L){
    if(L == NULL){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

// returns index of cursor
int index(List L){
    if(!L){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    }
    if(L->cursor){
        return L->index;
    }
    return -1;
}

// returns front data
int front(List L){
    if (!L || isEmpty(L)){
        printf("List front does not exist");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}

// returns back data
int back(List L){
    if (!L || isEmpty(L)){
        printf("List back does not exist");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}

// returns cursor data
int get(List L){
    if (!L || isEmpty(L)){
        printf("List cursor does not exist");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}

// returns whether two lists are equal
bool equals(List A, List B){
    if (A->length != B->length){
        return false;
    }
    Node atemp = A->front;
    Node btemp = B->front;
    while (atemp != NULL){
        if (atemp->data != btemp->data){
            return false;
        }
        atemp = atemp->next;
        btemp = btemp->next;
    }
    return true;
}


// Manipulation procedures ----------------------------------------------------

// clears a list
void clear(List L){
    if(!L){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    }
    while(!isEmpty(L)){
        deleteFront(L);
    }
    L->length = 0;
    L->index = -1; 
}

// set cursor data to x
void set(List L, int x){
    if(!L || isEmpty(L) || L->index < 0){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;   
}

// move cursor to front of list
void moveFront(List L){
    if(L && !isEmpty(L)){
        L->cursor = L->front;
        L->index = 0;
    }
}

// move cursor to back of list
void moveBack(List L){
    if(L && !isEmpty(L)){
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

// move cursor to previous node
void movePrev(List L){
    if (L->cursor && index(L) != 0){
        L->cursor = L->cursor->previous;
        L->index--;
    }
    else if (L->cursor && index(L) == 0){
        L->cursor = NULL;
        L->index = -1;
    }
}

// move cursor to next node
void moveNext(List L){
    if (L->cursor && index(L) != L->length){
        L->cursor = L->cursor->next;
        L->index++;
    }
    else if (L->cursor && index(L) == L->length){
        L->cursor = NULL;
        L->index = -1;
    }
}

// prepend a node to list
void prepend(List L, int x){
    Node N = newNode(x);
    if (isEmpty(L)){
        L->front = L->back = N;
    } else {
        N->next = L->front;
        L->front->previous = N;
        L->front = N;
    }
    L->length++;
    L->index++;
}

// append a node to list
void append(List L, int x){
    Node N = newNode(x);
    if (isEmpty(L)){
        L->front = L->back = N;
    } else {
        N->previous = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

// insert node before cursor
void insertBefore(List L, int x){
    Node N = newNode(x);
    if (isEmpty(L) && L->index != 0){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    } else {
        if (index(L) == 0){
            freeNode(&N);
            prepend(L, x);
            return;
        } else {  
            N->previous = L->cursor->previous;
            L->cursor->previous->next = N;
            N->next = L->cursor;
            L->cursor->previous = N;
        }
    }
    L->length++;
    L->index++;   
}

// insert node after cursor
void insertAfter(List L, int x){
    Node N = newNode(x);
    if (isEmpty(L) && L->index != 0){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    } else {
        if (index(L) + 1 == length(L)){
            freeNode(&N);
            append(L, x);
            return;
        } else {
            N->next = L->cursor->next;
            L->cursor->next->previous = N;
            N->previous = L->cursor;
            L->cursor->next = N;
        }
    }
    L->length++;
}

// delete front node
void deleteFront(List L){
    if (isEmpty(L) && L->index != 0){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    } else {
        if (L->front->next != NULL){
            L->front = L->front->next;
            freeNode(&L->front->previous);
        } else {
            freeNode(&L->front);
            L->front = NULL;
        }
    L->length--;
    L->index--;
    }
}

// delete back node
void deleteBack(List L){
    if (isEmpty(L) && L->index != 0){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    } else {
        if (index(L) + 1 == length(L)){
            L->index = -1;
        }
        if (L->back->previous != NULL){
            L->back = L->back->previous;
            freeNode(&L->back->next);
        } else {
            freeNode(&L->front);
            L->back = NULL;
        }
    L->length--;
    }
}

// delete node pointed at cursor
void delete(List L){
    if (isEmpty(L) && L->index != 0){
        printf("List does not exist");
        exit(EXIT_FAILURE);
    } else {
        if (index(L) == 0){
            deleteFront(L);
        } else if (index(L) + 1 == length(L)){
            deleteBack(L);
        } else {
            L->cursor->previous->next = L->cursor->next;
            L->cursor->next->previous = L->cursor->previous;
            freeNode(&L->cursor);
            L->length--;
            L->index = -1;
        }
    }
}

// Other Functions ------------------------------------------------------------

// print the list
void printList(FILE* out, List L){
    Node temp = L->front;
    while (temp != NULL){
        fprintf(out, "%d ", temp->data);
        temp = temp->next;
    }
    freeNode(&temp);   
}

// copy a list to another list
List copyList(List L){
    List nList = newList();
    Node temp  = L->front;
    while (temp != NULL){
        append(nList, temp->data);
        temp = temp->next;
    }
    return nList;
}

List concatList(List A, List B);
