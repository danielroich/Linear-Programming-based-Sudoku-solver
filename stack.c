#include "stack.h"

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->items = (BacktrackState*) malloc(capacity * sizeof(BacktrackState));
    stack->top_item = (BacktrackState*) malloc(sizeof(BacktrackState));
    return stack;
}

/* TODO: check if the default value is NULL while making malloc and non default value cannot be null */
int isEmpty(Stack* stack) {
    return stack->top_item == NULL; 
}