/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA3
 * * Graph.c
 * * This file holds the Graph ADT
*********************************************************************************/
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#include <string.h>

#define UNDEF -999
#define NIL 0

// GraphObj Struct
typedef struct GraphObj{
    List *listarray;
    int *color;
    int *parent;
    int *discovertime;
    int *finishtime;
    int order;
    int size;
} GraphObj;

// Graph initializing function
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj));
    G->listarray = malloc((n+1)*sizeof(List));
    for (int i = 1; i < n + 1; i++){
        G->listarray[i] = newList();
    }
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    for (int i = 1; i < n + 1; i++){
        G->parent[i] = NIL;
    }
    G->discovertime = calloc(n+1, sizeof(int));
    for (int i = 1; i < n + 1; i++){
        G->discovertime[i] = UNDEF;
    }
    G->finishtime = calloc(n+1, sizeof(int));
    for (int i = 1; i < n + 1; i++){
        G->finishtime[i] = UNDEF;
    }
    G->order = n;
    G->size = 0;
    return G;
}

// Frees the Graph
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL){
        for (int i = 1; i < (*pG)->order + 1; i++){
            freeList(&(*pG)->listarray[i]);
        }
        free((*pG)->listarray);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discovertime);
        free((*pG)->finishtime);
        free(*pG);
        *pG = NULL;
    }
}

// Gets the order of the Graph
int getOrder(Graph G){
    return G->order;    
}

// Gets the size of the Graph
int getSize(Graph G){
    return G->size;
}

// Gets the parent of the vertex
int getParent(Graph G, int u){
    if (u <= getOrder(G) || u >= 1){
        return G->parent[u];
    }
    printf("u not in range\n");
    exit(EXIT_FAILURE);
}

// Gets the discover time
int getDiscover(Graph G, int u){
    if (u <= getOrder(G) || u >= 1){
        return G->discovertime[u];
    }
    printf("u not in range\n");
    exit(EXIT_FAILURE);
}

// Gets the finish time
int getFinish(Graph G, int u){
    if (u <= getOrder(G) || u >= 1){
        return G->finishtime[u];
    }
    printf("u not in range\n");
    exit(EXIT_FAILURE);
}

// Adds an edge to the graph
void addEdge(Graph G, int u, int v){
    if (u < 1 || u > getOrder(G) || v > getOrder(G) ||  v < 1){
        return;
    }
    bool hasinsert = false;
    for(moveFront(G->listarray[v]); index(G->listarray[v]) >= 0; moveNext(G->listarray[v])){
        if (get(G->listarray[v]) < u){
            continue;
        } else {
            hasinsert = true;
            insertBefore(G->listarray[v], u);
            break;
        }
    }
    if (!hasinsert){
        append(G->listarray[v], u);
    }
    hasinsert = false;
    for(moveFront(G->listarray[u]); index(G->listarray[u]) >= 0; moveNext(G->listarray[u])){
        if (get(G->listarray[u]) < v){
            continue;
        } else {
            hasinsert = true;
            insertBefore(G->listarray[u], v);
            break;
        }
    }
    if (!hasinsert){
        append(G->listarray[u], v);
    }
    G->size++;
}

// Add an Arc to the graph
void addArc(Graph G, int u, int v){
    if (u < 1 || u > getOrder(G) || v > getOrder(G) ||  v < 1){
        return;
    }
    bool hasinsert = false;
    for(moveFront(G->listarray[u]); index(G->listarray[u]) >= 0; moveNext(G->listarray[u])){
        if (get(G->listarray[u]) < v){
            continue;
        } else {
            hasinsert = true;
            insertBefore(G->listarray[u], v);
            break;
        }
    }
    if (!hasinsert){
        append(G->listarray[u], v);
    }
    G->size++;
}

// Does DFS on the target graph in the order of the vertices in the list
void DFS(Graph G, List S){
    if (length(S) != G->order){
        printf("Length of S is not length of order\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G) + 1; i++){
        G->color[i] = 0;
        G->parent[i] = NIL;
    }
    int time = 1;
    for(moveFront(S); index(S) >= 0; moveNext(S)){
        if (G->color[get(S)] == 0){
            time = DFSVisit(G, get(S), time);
        }
    }
    clear(S);
    bool hasinsert = false;
    for (int i = 1; i < getOrder(G) + 1; i++){
        hasinsert = false;
        for(moveFront(S); index(S) >= 0; moveNext(S)){
            if (length(S) == 0){
                append(S, i);
            }
            if (G->finishtime[i] < G->finishtime[get(S)]){
                continue;
            } else {
                hasinsert = true;
                insertBefore(S, i);
                break;
            }
        }
        if (!hasinsert){
            append(S, i);
        }
     }
}

// Helper DFS function
int DFSVisit(Graph G, int u, int time){
    G->discovertime[u] = (time++);
    G->color[u] = 1;
    for(moveFront(G->listarray[u]); index(G->listarray[u]) >= 0; moveNext(G->listarray[u])){
        if (G->color[get(G->listarray[u])] == 0){
            G->parent[get(G->listarray[u])] = u;
            time = DFSVisit(G, get(G->listarray[u]), time);
        }
    }
    G->color[u] = 2;
    G->finishtime[u] = (time++);
    return time;
}

// Transposes a graph
Graph transpose(Graph G){
    Graph nGraph = newGraph(G->order);
    for (int i = 1; i < getOrder(G) + 1; i++){
        for(moveFront(G->listarray[i]); index(G->listarray[i]) >= 0; moveNext(G->listarray[i])){
            addArc(nGraph, get(G->listarray[i]), i);
        }
    }
    return nGraph;
}

// Copies a graph
Graph copyGraph(Graph G){
    Graph nGraph = newGraph(G->order);
    nGraph->size = G->size;
    for (int i = 1; i < getOrder(G) + 1; i++){
        nGraph->listarray[i] = copyList(G->listarray[i]);
    }
    for (int i = 1; i < getOrder(G) + 1; i++){
        nGraph->parent[i] = G->parent[i];
    }
    for (int i = 1; i < getOrder(G) + 1; i++){
        nGraph->discovertime[i] = G->discovertime[i];
    }
    for (int i = 1; i < getOrder(G) + 1; i++){
        nGraph->finishtime[i] = G->finishtime[i];
    }
    return nGraph;
}


// Print the Graph
void printGraph(FILE* out, Graph G){
    for (int i = 1; i < G->order + 1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->listarray[i]);
        fprintf(out, "\n");
    }
}
