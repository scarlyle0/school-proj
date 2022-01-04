#include "node.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
uint64_t branches;

Node *bst_create(void) {
    Node *bst = NULL;
    return bst;
}

// This function finds height of a binary search tree
// Accepts a node *
// Returns the height as uint32_t
// Based on BST Lecture 18
uint32_t bst_height(Node *root) {
    if (root) {
        uint32_t left = (bst_height(root->left));
        uint32_t right = (bst_height(root->right));
        // Return 1 + max(left or right)
        if (left > right) {
            return 1 + left;
        } else {
            return 1 + right;
        }
    }
    return 0;
}

// Returns the size of a binary search tree
// Accepts a node *
// Returns a uint32_t which is the size
uint32_t bst_size(Node *root) {
    if (root) {
        return 1 + bst_size(root->right) + bst_size(root->left);
    }
    return 0;
}

// This function finds if oldspeak is in the BST
// Accepts node * and char * oldspeak
// Returns the node * of the word if found, else returns NULL *
// Based on BST lecture 18
Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        // Go left if root->oldspeak is greater than oldspeak
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            if (!root->left) {
                return NULL;
            }
            branches++;
            return bst_find(root->left, oldspeak);
            // Go right if root->oldpseak is less than oldspeak
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            if (!root->right) {
                return NULL;
            }
            branches++;
            return bst_find(root->right, oldspeak);
        }
    }
    // Return root when root->oldspeak is == oldspeak
    return root;
}

// This function inserts a oldspeak/newspeak into a BST
// Accepts Node *, char * oldspeak/newspeak
// Returns the root node *  of the BST with added word node
// Does not insert duplicates
// Based on BST lecture 18
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    // Make sure no duplicates
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) == 0) {
            return root;
        }
        // If current root->oldspeak is greater than oldspeak
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            // Insert recursively in left subtree
            branches++;
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else {
            // Insert recursively in right subtree
            branches++;
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        // Return the root when going back up the recursive chain
        // So as to "update" the other nodes with the new node
        return root;
    }
    // If current node is NULL, make new node with oldspeak,newspeak
    return node_create(oldspeak, newspeak);
}

// This function prints out a BST contents
// Accepts a node *
// Returns nothing
// Based on BST lecture 18
void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}

// This function deletes a BST
// Accepts a node **
// Returns nothing
// Based on BST lecture 18
void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
}
