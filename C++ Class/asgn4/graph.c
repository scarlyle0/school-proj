#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Based on Assignment PDF
// Struct which holds a uint32_t, a boolean, a boolean array, and a matrix
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// Based on Assignment PDF
// This graph_create function allocates memory to a graph and
// Sets whether it is undirected and how many vertices it has
// Accepts parameters as a uint which is the num of vertices and
// a boolean which tells if the graph is undirected
// Returns the created graph
struct Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

// Based on Assignment PDF
// This function deletes a graph struct and frees it
// Accepts a double pointer to a graph
// Returns nothing
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

// This function returns the number of vertices in a graph
// Accepts a pointer to the graph as a parameter
// Returns the number of vertices in the graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// This function adds an edge to the graph
// Accepts a graph pointer, the two vertex, and the weight of the edge
// Returns false if edge couldnt be formed, returns true if edge was formed
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if ((i < START_VERTEX) || (i >= G->vertices) || (j < START_VERTEX) || (j >= G->vertices)) {
        return false;
    } else {
        G->matrix[i][j] = k;
        if (G->undirected == true) {
            G->matrix[j][i] = k;
        }
        return true;
    }
}

// This function returns whether a graph has an edge at vertices, i,j
// Accepts graph pointer, two vertices as uint32_t i,j
// Returns false is graph doesn't have an edge at ij, otherwise true
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i < START_VERTEX) || (i >= G->vertices) || (j < START_VERTEX) || (j >= G->vertices)
        || (G->matrix[i][j] == 0)) {
        return false;
    } else {
        return true;
    }
}

// This function returns weight of edge at ij
// Accepts graph pointer, and two vertices as uint32_t i,j
// Return the weight of the edge
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((graph_has_edge(G, i, j) == false) || (i < START_VERTEX) || (i >= G->vertices)
        || (j < START_VERTEX) || (j >= G->vertices)) {
        return 0;
    } else {
        return G->matrix[i][j];
    }
}

// This function returns whether a vertex is marked visited
// Accepts graph pointer, and one vertex as a uint32_t
// Returns whether graph is marked as visited
bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v] == true) {
        return true;
    } else {
        return false;
    }
}

// This functions marks a vertex as visited
// Accepts graph pointer, and one vertex as a uint32_t
// Returns nothing
void graph_mark_visited(Graph *G, uint32_t v) {
    if ((v >= START_VERTEX) && (v < G->vertices)) {
        G->visited[v] = true;
    }
    return;
}

// This functions marks a vertex as unvisited
// Accepts graph pointer, and one vertex as a uint32_t
// Returns nothing
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if ((v >= START_VERTEX) && (v < G->vertices)) {
        G->visited[v] = false;
    }
    return;
}

// This function is used for debugging and prints a graph
// Accepts a graph pointer as a parameter
// Returns nothing
void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        printf("\n");
        for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%2" PRIu32, G->matrix[i][j]);
        }
    }
    printf("\n");
    return;
}
