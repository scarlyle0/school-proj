#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Based on Assignment PDF
// Stack struct holding two uint32_t and a array of uint32_t
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// Based on Assignment PDF
// This function creates a stack and allocates memory to it
// Accepts a uint32_t capacity, which is capacity of stack
// Returns the stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Based on Assignment PDF
// This function deletes the stack and frees memory
// Accepts a double pointer to stack
// Returns nothing
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// This function returns size of stack
// Accepts pointer to stack
// Returns size of stack
uint32_t stack_size(Stack *s) {
    return (s->top);
}

// This function checks whether stack is empty
// Accepts pointer to stack
// Returns true if stack is empty, false if it is not
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

// This function checks whether stack is full
// Accepts pointer to stack
// Returns true is stack if full, false is it is not
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

// This function pushes a uint32_t to stack
// Accepts pointer to stack, and uint32_t
// Returns false if stack is full, else returns true
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = x;
        s->top += 1;
        return true;
    }
}

// This function pops a uint32_t from the stack
// Accepts pointer to stack, and pointer to uint32_t
// Returns false if stack is empty, else returns true
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top - 1];
        s->top -= 1;
        return true;
    }
}

// This function peeks a uint32_t from the stack
// Accepts pointer to stack, and pointer to uint32_t
// Returns false if stack is empty, else returns true
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top - 1];
        return true;
    }
}

// This function copies a stack to another stack
// Accepts pointer to destination stack, and pointer to source stack
// Returns nothing
void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;
    dst->capacity = src->capacity;
    for (uint32_t i = 0; i < src->capacity; i++) {
        dst->items[i] = src->items[i];
    }
}

// Based on Assignment PDF
// This function prints out a stack
// Accepts pointer to stack, pointer to outfile, and pointer to array of strings
// Returns nothing
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
