/*********************************************************************************
* Sean Carlyle, scarlyle
* 2022 Winter CSE101 PA1
* Lex.c
* Sorts an infile by line lexographically
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char **argv) {
    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];

   // Get input
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

   line_count = 0;
   while(fgets(line, MAX_LEN, in) != NULL){
      line_count++;
   }
   rewind(in);
   char **array = malloc(line_count*sizeof(char*));
   for (int i = 0; i < line_count; i++){
       array[i] = (char*) malloc(MAX_LEN+1);
   }
   
   // Copy read in lines into the array
   int counter = 0;
   while(fgets(line, MAX_LEN, in) != NULL){
       strcpy(array[counter], line);
       counter++;
   } 
   
   // Add each string to the list in sorted order
   List sort = newList();
   append(sort, 0);
   bool hasinsert = false;
   for (int i = 1; i < line_count; i++){
       hasinsert = false;
       for(moveFront(sort); index(sort) >= 0; moveNext(sort)){
           if (strcmp(array[i],array[get(sort)]) >= 0){
               continue;
           } else {
               hasinsert = true;
               insertBefore(sort, i);
               break;
           }
       }
       if (!hasinsert){
           append(sort, i);
       }

   }
   
   // Print the lines out to the outfile in the order of the indexes in the List
   for(moveFront(sort); index(sort) >= 0; moveNext(sort)){
       fprintf(out, "%s", array[get(sort)]);
   }
  
   
   // Free everything
   fclose(in);
   fclose(out);
   freeList(&sort);
    
   for (int i = 0; i < line_count; i++){
       free(array[i]);
   }
   free(array);
   return 0;
    
}
