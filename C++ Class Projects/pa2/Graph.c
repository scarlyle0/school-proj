/*********************************************************************************
 * * Sean Carlyle, scarlyle
 * * 2022 Winter CSE101 PA2
 * * Graph.c
 * * This file holds the Graph ADT
*********************************************************************************/
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#include <string.h>

#define INF -999
#define NIL 999

// GraphObj Struct
typedef struct GraphObj{
    List *listarray;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;
    int source;
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
    G->distance = calloc(n+1, sizeof(int));
    for (int i = 1; i < n + 1; i++){
        G->distance[i] = INF;
    }
    G->order = n;
    G->size = 0;
    G->source = NIL;
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
        free((*pG)->distance);
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

// Gets the source of the Graph
int getSource(Graph G){
    return G->source;
}

// Gets the parent of the vertex
int getParent(Graph G, int u){
    if (u <= getOrder(G) || u >= 1){
        return G->parent[u];
    }
    printf("u not in range\n");
    exit(EXIT_FAILURE);
}

// Gets the distance of the vertex from the source
int getDist(Graph G, int u){
    if (u <= getOrder(G) || u >= 1){
        return G->distance[u];
    }
    printf("u not in range\n");
    exit(EXIT_FAILURE);
}

// Gets the List of vertexes that make the shortest path to the source
void getPath(List L, Graph G, int u){
    if (getSource(G) != NIL && (getOrder(G) >= u && u >= 1)){
        if(u == G->source){
            append(L, G->source);
        }
        else if (G->parent[u] == NIL){
            append(L, NIL);
        }
        else {
            getPath(L, G, G->parent[u]);
            append(L, u);
        }
    }
}

// Clear the graph
void makeNull(Graph G){
    for (int i = 1; i < getOrder(G) + 1; i++){
        clear(G->listarray[i]);
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
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

// Do BFS on a source vertex and assign distances and parents to vertices
void BFS(Graph G, int s){
    G->source = s;
    for (int i = 1; i < getOrder(G) + 1; i++){
        if (i == s){
            continue;
        }
        G->color[i] = 0;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = 1;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List L = newList();
    append(L, s);
    while (!isEmpty(L)){
        moveFront(L);
        int x = get(L);
        deleteFront(L);
        for(moveFront(G->listarray[x]); index(G->listarray[x]) >= 0; moveNext(G->listarray[x])){
            if (G->color[get(G->listarray[x])] == 0){
                G->color[get(G->listarray[x])] = 1;
                G->distance[get(G->listarray[x])] = G->distance[x] + 1;
                G->parent[get(G->listarray[x])] = x;
                append(L, get(G->listarray[x]));
            }
        }
        G->color[x] = 2;
    }
    freeList(&L); 
}

// Print the Graph
void printGraph(FILE* out, Graph G){
    for (int i = 1; i < G->order + 1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->listarray[i]);
        fprintf(out, "\n");
    }
}
