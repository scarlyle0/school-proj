#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"
#include "io.h"
#include "header.h"
#include "stack.h"

#include <stdint.h>
#include <stdio.h>

// This function builds the huffman tree
// Accepts a histogram which is an array of uint64_t
// Returns the root node of huffman tree
// Used pseudo from assignment PDF
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET);
    // Insert node into pq for every histogram symbol
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }
    // Dequeue nodes, join them and enqueue parent
    while (pq_size(q) > 1) {
        Node *left = NULL;
        Node *right = NULL;
        dequeue(q, &left);
        dequeue(q, &right);
        Node *parent = node_join(left, right);
        enqueue(q, parent);
    }
    // Last node left in pq is the root node
    Node *root = NULL;
    dequeue(q, &root);
    pq_delete(&q);
    return root;
}

// This function builds a code table
// Accepts a pointer to root node and an array of codes
// Returns nothing
// Used pseudo from assignment PDF
void build_codes(Node *root, Code table[static ALPHABET]) {
    // Traverse through huffman tree if a leaf add symbol to table
    // Push a 0 to c if interior, when returning pop it and push a 1
    // Pop the it when returning.
    static Code c;
    static bool init = false;
    uint8_t i;
    if (init == false) {
        c = code_init();
        init = true;
    }
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, &i);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &i);
        }
    }
}

// This function writes the huffman tree to outfile
// Accepts outfile descriptor and pointer to root node
// Returns nothing
// Used pseudo from assignment PDF
void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (root->left == NULL && root->right == NULL) {
            uint8_t l = 76;
            write_bytes(outfile, &l, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            uint8_t r = 73;
            write_bytes(outfile, &r, 1);
        }
    }
}

// This function rebuilds the huffman tree
// Accepts uint16 nbytes and array of uint8 tree
// Returns root node of huffman tree
// Used pseudo from assignment PDF
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(nbytes);
    // For size of tree dump
    // If reach L push node with next symbol
    // Skip symbol since already in node
    for (uint32_t i = 0; i < nbytes; i++) {
        if (tree[i] == 76) {
            Node *n = node_create(tree[i + 1], 0);
            stack_push(s, n);
            i++;
            // If reach I pop two nodes, join them, push their parent
        } else if (tree[i] == 73) {
            Node *left = NULL;
            Node *right = NULL;
            stack_pop(s, &right);
            stack_pop(s, &left);
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }
    // Last node in stack is root node
    Node *root = NULL;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

// This function deletes the huffman tree
// Accepts double pointer to root node
// Returns nothing
void delete_tree(Node **root) {
    // Traverse through huffman tree deleting leaves
    if ((*root) != NULL) {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            node_delete(root);
        } else {
            delete_tree(&(*root)->left);
            delete_tree(&(*root)->right);
            // On the way back up, if interiors are now leaves delete them
            if ((*root)->left == NULL && (*root)->right == NULL) {
                node_delete(root);
            }
        }
    }
}
