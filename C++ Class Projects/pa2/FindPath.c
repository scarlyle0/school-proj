/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA2
 * * FindPath.c
 * * Takes an infile, prints a graph and finds the shortest path from a vertex to a source vertex
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
    bool first = false;
    bool second = false;
    // Read in order of Graph
    fgets(line, MAX_LEN, in);
    Graph G = newGraph(atoi(line));
    // Reads in rest of infile
    while(fgets(line, MAX_LEN, in) != NULL){
        // Extract two vertices
        sscanf(line, "%d %d", &one, &two);
        if (one == 0 && two == 0){
            if (!first){
                // Print out graph in first half infile numbers
                printGraph(out, G);
                fprintf(out, "\n");
                first = true;
            }
            second = true;
            continue;
        }
        if (second){
             // Search the source and print out stuff distance from source
             BFS(G, one);
             if (getDist(G,two) == INF){
                 fprintf(out, "The distance from %d to %d is infinity\n", one, two);
                 fprintf(out, "No %d-%d path exists\n", one, two);
                 fprintf(out, "\n\n");
             } else {
                 fprintf(out, "The distance from %d to %d is %d\n", one, two, getDist(G, two));
                 fprintf(out, "A shortest %d-%d path is: ", one, two);
                 List L = newList();
                 getPath(L, G, two);
                 printList(out, L);
                 clear(L);
                 freeList(&L);
                 fprintf(out, "\n\n");   
            }
        }
        // Add edge to graph
        if (!second){
            addEdge(G, one, two);
        }
    }
    freeGraph(&G);
    fclose(in);
    fclose(out);
    return 0;
}

