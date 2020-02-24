
#ifndef SOFTWAREPROJ_STACK_H
#define SOFTWAREPROJ_STACK_H

#include "backtrack_state.h"

typedef struct _Stack {
    int top_item_index;
    BacktrackState* items;
    int capacity;
} Stack;

int isEmpty(Stack* stack); 
void push(Stack* stack, BacktrackState item);
BacktrackState pop(Stack* stack);
BacktrackState peek(Stack* stack);
Stack* createStack(int capacity);

#endif