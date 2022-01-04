#include "node.h"
#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// This function creates and initializes a stack
// Accepts uint capacity of stack
// Returns created stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// This function deletes a stack
// Accepts double pointer to stack
// Returns nothing
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// This function tells whether stack is empty
// Accepts a pointer to stack
// Returns true if empty, otherwise false
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

// This function tells whether stack is full
// Accepts a pointer to stack
// Returns true if full, otherwise false
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

// This functions tells stack size
// Accepts pointer to stack
// Returns stack size
uint32_t stack_size(Stack *s) {
    return (s->top);
}

// This function pushes a node to stack
// Accepts pointer to stack and pointer to node
// Returns false if full, true on success
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top += 1;
        return true;
    }
}

// This function pops a node from stack
// Accepts pointer to stack and pointer to node
// Returns false if empty, true on success
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    } else {
        *n = s->items[s->top - 1];
        s->top -= 1;
        return true;
    }
}

// This function prints a stack for debug
// Accepts a pointer to stack
// Returns nothing
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        node_print(s->items[i]);
    }
}
