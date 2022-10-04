/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA3
 * * FindComponents.c
 * * Finds the strongly connected components of a graph 
*********************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 300
int main(int argc, char **argv) {
    FILE *in, *out;
    char line[MAX_LEN];
    
    // Get the user input
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

    int one = 0;
    int two = 0;
    // Read in order of Graph
    fgets(line, MAX_LEN, in);
    Graph G = newGraph(atoi(line));
    // Reads in rest of infile
    while(fgets(line, MAX_LEN, in) != NULL){
        // Extract two vertices
        sscanf(line, "%d %d", &one, &two);
        addArc(G, one, two);
    }

    // print adjacency list
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // Find Strongly Connected components
    List S = newList();
    for(int i=1; i<=getOrder(G); i++) append(S, i);
    Graph T = NULL;
    DFS(G, S);
    T = transpose(G);
    DFS(T, S);
    int counter = 0; 
    for(moveFront(S); index(S) >= 0; moveNext(S)){
        if (getParent(T, get(S)) == 0){
            counter++;
        }
    }

    // Print out strongly connected components
    fprintf(out, "\nG contains %d strongly connected components:\n", counter);
        
    List L = newList();
    
    int counter_two = 0;
    for(moveBack(S); index(S) >= 0; movePrev(S)){
        prepend(L, get(S));
        if (getParent(T, get(S)) == 0){
            counter_two++;
            fprintf(out, "Component %d: ", counter_two);
            printList(out, L);
            clear(L);
            fprintf(out, "\n");
        }   
    }

    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeList(&L);
    fclose(in);
    fclose(out);
    return 0;
}


