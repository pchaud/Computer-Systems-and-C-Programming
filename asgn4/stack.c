#include "stack.h"

#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    uint32_t capacity;
    uint32_t top;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    // Attempt to allocate memory for a stack
    // Cast it to a stack pointer too!
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->capacity = capacity;
    s->top = 0;
    // We need enough memory for <capacity> numbers
    s->items = calloc(s->capacity, sizeof(uint32_t));
    // We created our stack, return it!
    return s;
}

void stack_free(Stack **sp) {
    // sp is a double pointer, so we have to check if it,
    // or the pointer it points to is null.
    if (sp != NULL && *sp != NULL) {
        // Of course, we have to remember to free the
        // memory for the array of items first,
        // as that was also dynamically allocated!
        // If we freed the Stack first then we would
        // not be able to access the array to free it.
        if ((*sp)->items) {
            free((*sp)->items);
            (*sp)->items = NULL;
        }
        // Free memory allocated for the stack
        free(*sp);
    }
    if (sp != NULL) {
        // Set the pointer to null! This ensures we dont ever do a double free!
        *sp = NULL;
    }
}

bool stack_push(Stack *s, uint32_t val) {
    // If the stack is empty, return false;
    if (stack_full(s)) {
        return false;
    }
    // Set val
    s->items[s->top] = val;
    // Move the top of the stack
    s->top++;
    return true;
}

bool stack_pop(Stack *s, uint32_t *val) {
    //If the stack is empty, return false
    if (stack_empty(s)) {
        return false;
    }
    //Set integer pointed to by val to the last item on the stack
    //We subtract 1 to get the last item on the stack- could put decrementation
    //before the *val defintion and leave it as [s->top] as well
    *val = s->items[s->top - 1];
    s->top--;
    return true;
}

bool stack_peek(const Stack *s, uint32_t *val) {
    //If the stack is empty, return false
    if (stack_empty(s)) {
        return false;
    }

    //sets the integer pointed to by val to the last item on the stack

    *val = s->items[s->top - 1];
    return true;

    //if(*val != temp){
    //return true;
    //}
    //else{
    //return false;
    //}
}

bool stack_empty(const Stack *s) {
    //If the stack is empty, return true
    //Otherwise return false
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool stack_full(const Stack *s) {
    //If the stack is full, return true, otherwise return false
    //Compares the top of the stack to the capacity
    if (s->top == s->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t stack_size(const Stack *s) {
    //If the stack is empty, return 0
    //if (stack_full(s)){
    //return 0;
    //}

    //else return the number of elements in the the stack (opposite of logic used in stack_peek)

    return s->top;
}

void stack_copy(Stack *dst, const Stack *src) {
    //using the assert function to ensure the capacity of dst is large enough for the number of items
    //in the stack (src)
    assert(dst->capacity >= src->top);

    //iterating through the stack to copy each item from the source to destination stack
    for (uint32_t index = 0; index < src->top; index += 1) {
        dst->items[index] = src->items[index];
    }

    //updating dst->top so that it is known how many items are now in the stack
    dst->top = src->top;
}

void stack_print(const Stack *s, FILE *f, char *vals[]) {
    //prints out the stack as a list starting at the bottom of the stack
    //should print each element in the order they were pushed into on the stack
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(f, "%s\n", vals[s->items[i]]);
    }
}
