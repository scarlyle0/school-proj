#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Struct based on Assignment PDF
// Struct path holds a stack and uint32_t
struct Path {
    Stack *vertices;
    uint32_t length;
};

// This function creates a path and allocates memory to the path
// Accepts nothing
// Returns the path
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

// This function deletes the path and frees its memory
// Accepts a double pointer to the path
// Returns nothing
void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
    return;
}

// This function pushes a vertex to the path if able
// Accepts path pointer, a vertex, and a graph pointer
// Returns false if it fails, true if succeeds
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t old_top = 0;
    bool no_vertices = false;
    if (!stack_peek(p->vertices, &old_top)) { // Mark if there are no vertices
        no_vertices = true;
    }
    if (!stack_push(p->vertices, v)) {
        return false;
    } else {
        if (!no_vertices) { // If there are vertices add length
            p->length += graph_edge_weight(G, old_top, v);
        }
        return true;
    }
}

// This function pops a vertex to the path if able
// Accepts path pointer, a vertex, and a graph pointer
// Returns false if it fails, true if succeeds
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t new_top = 0;
    if (!stack_pop(p->vertices, v)) {
        return false;
    } else {
        if (!stack_peek(p->vertices, &new_top)) {
            p->length = 0;
        }
        p->length -= graph_edge_weight(G, new_top, *v);
        return true;
    }
}

// This function returns size of path
// Accepts pointer to path
// Returns number of vertices in path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// This function returns path length
// Accepts pointer to path
// Returns length of path
uint32_t path_length(Path *p) {
    return p->length;
}

// This function copies a path to another
// Accepts a destination path, and a source path
// Returns nothing
void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

// This function prints out a path
// Accepts a pointer to path, pointer to outfile, pointer to string array
// Returns nothing
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %u\n", path_length(p));
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
}
