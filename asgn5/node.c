#include "node.h"
#include <stdlib.h>
#include <stdio.h>

// This function initializes node ADT
// Accepts uint8 symbol and frequency
// Returns the initialized node
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// This function deletes the node
// Accepts double node pointer
// Returns nothing
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

// This function joins two nodes to a parent
// Accepts pointer to left node and pointer to right
// Returns parent node
Node *node_join(Node *left, Node *right) {
    Node *n = node_create(36, left->frequency + right->frequency);
    n->left = left;
    n->right = right;
    return n;
}

// Prints out a node for debug
// Accepts node pointer
// Returns nothing
void node_print(Node *n) {
    printf("symbol: %u frequency: %lu\n", n->symbol, n->frequency);
    if (n->left != NULL && n->right != NULL) {
        node_print(n->left);
        node_print(n->right);
    }
}
