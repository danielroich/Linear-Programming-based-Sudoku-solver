
#ifndef SOFTWAREPROJ_STACK_H
#define SOFTWAREPROJ_STACK_H

#include "backtrack_state.h"
#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h>

typedef struct _Stack {
    BacktrackState* top_item;
    BacktrackState* items;
    unsigned capacity;
} Stack;

int isEmpty(Stack* stack);
void push(Stack* stack, BacktrackState item);
BacktrackState pop(Stack* stack);
BacktrackState peek(Stack* stack);
Stack* createStack(unsigned capacity);

#endif