/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");
   printf("passed\n");
   //printf("index: %d\n", index(A));
   //moveFront(A);
   //printf("index: %d\n", index(A));
   for(moveFront(A); index(A)>=0; moveNext(A)){
      //printf("yo");
      printf("%d ", get(A));
   }   
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");
   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");
   
   //printList(stdout,A);
   //printf("yo\n");

   moveFront(A);
   insertBefore(A, -1);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   //printList(stdout,A);
   //printf("\n");
   //printf("added: %d\n", length(A));
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   clear(A);
   /*printList(stdout,A);
   printf("\n");
   append(A, 1);
   append(A, 2);
   printList(stdout,A);
   printf("\n");
   moveFront(A);
   delete(A);
   printList(stdout,A);
   printf("\n");
   append(A, 3);
   append(A, 5);
   moveFront(A);
   printf("index: %d\n", index(A));
   insertAfter(A, 12);
   printList(stdout,A);
   printf("\n");
   printf("index: %d\n", index(A));
   delete(A);
   printList(stdout,A);
   printf("\n");
   if (length(A) != 3) printf("NOOOO!\n");
  
   prepend(A, 5);
   append(A, 7);
   prepend(A, 2);
   moveFront(A);
   printf("index: %d\n", index(A));
   insertBefore(A, 43);
   printf("index: %d\n", index(A));
   printList(stdout,A);
   printf("\n");
   deleteFront(A);
   printf("index: %d\n", index(A));
   printList(stdout,A);
   printf("\n");
   delete(A);
   if (front(A) != 5) printf("NOOOO!\n");;
   */
   prepend(A, 5); 
   prepend(A, 65);
   prepend(A, 43);
   prepend(A, 2);
   prepend(A, 8);
   prepend(A, 1);
   printList(stdout,A);
   printf("\n");
   moveBack(A);
   //moveFront(A);
   //return 0;   
   deleteBack(A);
   //deleteFront(A);
   printList(stdout,A);
   printf("\n");
   printf("index: %d\n", index(A));
   if (index(A) != -1) printf("NOOOO!\n");
   moveFront(A);
   printf("index: %d\n", index(A));  
   deleteBack(A);
   printList(stdout,A);
   printf("\n");
   moveNext(A);
   if (index(A) != 1) printf("NOOOO!\n");



   freeList(&A); 
   freeList(&B);
   freeList(&C);
   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/
