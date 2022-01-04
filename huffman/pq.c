#include "node.h"
#include "pq.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

struct PriorityQueue {
    uint32_t size;
    uint32_t capacity;
    Node **N;
};

// Creates and initializes a PriorityQueue
// Accepts capacity uinteger
// Returns created PriorityQueue
// The checking if created is from lecture
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->size = 0;
        q->N = (Node **) calloc(capacity, sizeof(Node *));
        if (q->N) {
            return q;
        }
    }
    free(q);
    return (PriorityQueue *) 0;
}

// This function deletes a pq
// Accepts double pointer to pq
// Returns nothing
void pq_delete(PriorityQueue **q) {
    if (*q) {
        free((*q)->N);
        free(*q);
        *q = NULL;
    }
}

// This function checks if pq is empty
// Accepts pointer to pq
// Returns true if empty, false otherwise
bool pq_empty(PriorityQueue *q) {
    if (q) {
        if (q->size == 0) {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

// This function checks if pq is full
// Accepts a pointer to pq
// Returns true is at capacity, false otherwise
bool pq_full(PriorityQueue *q) {
    if (q) {
        if (q->size == q->capacity) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}

// This function returns a pq's size
// Accepts a pointer to pq
// Returns size of pq
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// This function enqueues nodes into the pq
// It keeps them in min heap order
// Accepts pq pointer and node pointer
// Returns true/false on success/failure
bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    } else {
        q->N[q->size] = n;
        q->size++;
        if (q->size > 1) {
            uint32_t parent_index = floor(q->size / 2);
            uint32_t child_index = q->size;
            // Swap upwards until node is in right place
            while (q->N[child_index - 1]->frequency < q->N[parent_index - 1]->frequency) {
                Node *temp = q->N[child_index - 1];
                q->N[child_index - 1] = q->N[parent_index - 1];
                q->N[parent_index - 1] = temp;
                child_index = parent_index;
                if (child_index == 1) {
                    return true;
                }
                parent_index = floor(child_index / 2);
            }
        }
        return true;
    }
}

// This function returns the min child of two node children
// Accepts pointer to pq, index of first child, index of last child
// Returns index of smaller child
uint32_t min_child(PriorityQueue *q, uint32_t first, uint32_t last) {
    uint32_t left = (2 * first);
    uint32_t right = (left + 1);
    if (right <= last && q->N[right - 1]->frequency < q->N[left - 1]->frequency) {
        return right;
    }
    return left;
}

// This function dequeues smallest node and switches the last node to first
// It then sorts the last node into the correct place by comparing downwards
// Swaps until it is in the right place
// This function accepts pointer to pq and double pointer to node
// Returns true on success, false on failure
// Used fix_heap from assignment 3 which was based on assignment 3 PDF
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    q->size--;
    // Return top node, replace it with last node
    *n = q->N[0];
    q->N[0] = q->N[q->size];
    bool found = false;
    uint32_t parent_index = 1;
    uint32_t child_index = min_child(q, parent_index, q->size);

    // Swap downwards until node is in min heap order
    while (parent_index <= floor(q->size / 2) && !found) {
        if (q->N[parent_index - 1]->frequency > q->N[child_index - 1]->frequency) {
            Node *temp = q->N[child_index - 1];
            q->N[child_index - 1] = q->N[parent_index - 1];
            q->N[parent_index - 1] = temp;
            parent_index = child_index;
            child_index = min_child(q, parent_index, q->size);
        } else {
            found = true;
        }
    }
    return true;
}

// This function prints a pq for debug
// Accepts pointer to pq
// Returns nothing
void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i++) {
        node_print(q->N[i]);
    }
}
