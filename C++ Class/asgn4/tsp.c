#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"

static int counter;

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose);

// This is the main function, it takes user input through getopt
// and uses a infile to find the shortest hamiltonian path to take
// Accepts parameters argc, char **argv for user input
// Returns an integer, in this case 0
// Based off getopt code from Eugene section
int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool undirected = false;
    bool verbose = false;
    bool help = false;
    int opt = 0;
    infile = stdin;
    // Get user input using optarg
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'u': undirected = true; break;
        }
    }
    // Help message
    if (help) {
        printf("SYNOPSIS\n  Traveling Salesman Problem using DFS.\n\n");
        printf("USAGE\n  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n");
        printf("OPTIONS\n  -u             Use undirected graph.\n  -v             Enable verbose "
               "printing.\n"
               "  -h             Program usage and help.\n"
               "  -i infile      Input containing graph (default: stdin)\n  -o outfile     Output "
               "of computed path (default: stdout)\n");
    } else {
        char buf[1024];
        uint32_t num_vertices = 0;
        uint32_t vertex_one = 0;
        uint32_t vertex_two = 0;
        uint32_t vertex_weight = 0;
        // Get first line of file and assign it to num_vertices
        fgets(buf, 1024, infile);
        sscanf(buf, "%u", &num_vertices);
        // Allocate memory and create graph and cities
        Graph *G = graph_create(num_vertices, undirected);
        char **cities = (char **) malloc(num_vertices * sizeof(char *));
        for (uint32_t i = 0; i < num_vertices; i++) {
            cities[i] = (char *) calloc(num_vertices + 2, sizeof(char));
        }
        // Add city names to city array
        for (uint32_t i = 0; i < num_vertices; i++) {
            fgets(buf, 1024, infile);
            buf[strlen(buf) - 1] = '\0';
            strcpy(cities[i], buf);
        }
        // Get the rest of the file which are the edges of the vertices
        // Add them to the graph unless they are malformed
        while (NULL != fgets(buf, 1024, infile)) {
            sscanf(buf, "%u %u %u", &vertex_one, &vertex_two, &vertex_weight);
            if (!graph_add_edge(G, vertex_one, vertex_two, vertex_weight)) {
                fprintf(outfile, "Error: malformed edge\n");
                return 0;
            }
        }

        // Allocate memory and create paths
        Path *current_path = path_create();
        Path *shortest_path = path_create();
        dfs(G, START_VERTEX, current_path, shortest_path, cities, outfile, verbose);
        // Print path and total recursive calls
        path_print(shortest_path, outfile, cities);
        fprintf(outfile, "Total recursive calls: %d\n", counter);
        // Free allocated memory and delete structures
        for (uint32_t i = 0; i < num_vertices; i++) {
            free(cities[i]);
            cities[i] = NULL;
        }
        fclose(infile);
        free(cities);
        cities = NULL;

        graph_delete(&G);
        path_delete(&current_path);
        path_delete(&shortest_path);
        counter = 0;
        return 0;
    }
}

// This function performs depth first search in order to find the shortest hamiltonian path
// Accepts parameters as a graph, vertices, current path, shortest path, a pointer to an array of strings
// A pointer to an outfile and a boolean called verbose
// Returns nothing
// Based of Pseudocode from Assignment
void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {
    counter++;
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    // If path length is every greater than the shortest and shortest has been set
    // Mark unvisited and pop vertices then return, stopping travel down this path
    if ((path_length(curr) > path_length(shortest)) && (path_length(shortest) != 0)) {
        if (!(path_vertices(curr) == (graph_vertices(G) + 1))) {
            graph_mark_unvisited(G, v);
        }
        path_pop_vertex(curr, &v, G);
        return;
    }
    // If the graph has reached every vertices and has an edge with the start vertex
    // Mark the start vertex as travelable
    if (path_vertices(curr) == (graph_vertices(G)) && (graph_has_edge(G, v, 0))) {
        graph_mark_unvisited(G, 0);
    }
    // If the path is complete
    if (path_vertices(curr) == (graph_vertices(G) + 1)) {
        if (verbose) { // Print the path if verbose is on
            path_print(curr, outfile, cities);
        }
        // If the current completed path is less than than the recorded shortest
        // Copy the path
        if ((path_length(curr) < path_length(shortest)) || path_length(shortest) == 0) {
            path_copy(shortest, curr);
        }
    }
    // For every edge connected to vertex v, call dfs on them
    // if they are marked unvisited.
    for (uint32_t i = 0; i < graph_vertices(G); i++) {
        if ((graph_has_edge(G, v, i)) && (!graph_visited(G, i))) {
            dfs(G, i, curr, shortest, cities, outfile, verbose);
        }
    }
    // If the path is not completed mark vertex unvisited
    if (!(path_vertices(curr) == (graph_vertices(G) + 1))) {
        graph_mark_unvisited(G, v);
    }
    path_pop_vertex(curr, &v, G);
}
