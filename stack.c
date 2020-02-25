#include "stack.h"
#include <stdlib.h>

Stack* createStack(int capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->items = (BacktrackState*) malloc(capacity * sizeof(BacktrackState));
    stack->top_item_index = -1;
    return stack;
}

/* TODO: check if the default value is NULL while making malloc and non default value cannot be null */
int isEmpty(Stack* stack) {
    return stack->top_item_index == -1; 
}

int isFull(Stack* stack) 
{ 
    return stack->top_item_index == stack->capacity - 1; 
} 

void push(Stack* stack, BacktrackState item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->items[++(stack->top_item_index)] = item; 
} 

BacktrackState pop(Stack* stack) 
{ 
    BacktrackState default_state = {-1,-1,0,NULL,0,1};
    if (isEmpty(stack)) 

        // because it was initilized on the stack, the value could not be used outside
        return default_state;
    return stack->items[(stack->top_item_index)--]; 
} 

// Function to return the top from stack without removing it 
BacktrackState peek(Stack* stack) 
{ 
     BacktrackState default_state = {-1,-1,0,NULL,0,1};
    if (isEmpty(stack)) {
         // because it was initilized on the stack, the value could not be used outside
        return default_state;
    }
    return stack->items[stack->top_item_index]; 
} 