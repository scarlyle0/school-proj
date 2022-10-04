/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA2
 * * GraphTest.c
 * * GraphTest for testing Graph functionality
*********************************************************************************/

#include "List.h"
#include "Graph.h"

int main(void){
/*
 * Graph G = newGraph(6);
 * addEdge(G, 1, 2);
 * addEdge(G, 1, 3);
 * addEdge(G, 2, 4);
 * addEdge(G, 3, 4);
 * addEdge(G, 4, 5);
 * addEdge(G, 5, 6);
 * addEdge(G, 5, 2);
 * addEdge(G, 6, 2);
 * printGraph(stdout, G);
 * BFS(G,1);
 * printf("\n");
 * printf("\n");
 * printf("\n");
 * printf("\n");
 * printf("\n");
 * printf("\n");
 * printGraph(stdout, G);
 *
 *
 * List L = newList();
 * append(L, 1);
 * moveBack(L);
 * int x = get(L);
 * deleteBack(L);
 *
 * append(L, 3);
 *
 * printList(stdout, L);
 * printf("\n");
 * printf("%d\n", x);
 *
 * freeGraph(&G);
 * */


Graph A = newGraph(100);


if (getSource(A) != NIL) printf("yo\n");
BFS(A, 42);
if (getSource(A) != 42) printf("yo\n");
BFS(A, 88);
if (getSource(A) != 88) printf("yo\n");
return 0;
}

