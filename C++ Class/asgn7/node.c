#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// This function creates a node
// Accepts char * oldspeak/newspeak
// Returns the * to the new node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (!newspeak) {
        n->newspeak = NULL;
    } else {
        n->newspeak = strdup(newspeak);
    }
    n->oldspeak = strdup(oldspeak);
    n->left = NULL;
    n->right = NULL;
    return n;
}

// This function deletes a node
// Accepts a Node **
// Returns nothing
void node_delete(Node **n) {
    if (*n) {
        if ((*n)->newspeak) {
            free((*n)->newspeak);
        }
        free((*n)->oldspeak);
        free(*n);
        *n = NULL;
    }
}

// This function prints a node
// Accepts a Node *
// Returns nothing
void node_print(Node *n) {
    if (n->newspeak && n->oldspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->oldspeak && !n->newspeak) {
        printf("%s\n", n->oldspeak);
    }
}
