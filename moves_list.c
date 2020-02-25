#include "moves_list.h"
#include "stdio.h"
#include "stdlib.h"

/* for moves: set, autofill, generate, guess */
void clean_nexts(Moves* moves){
    if(moves && (moves->curr)){
        (moves->curr)->next=NULL;
    }
}

/* for move: reset */
void back_to_first_move(Moves* moves){
    if(moves && (moves->curr)){
        while((moves->curr)->prev)
        {
            moves->curr = (moves->curr)->prev;
        }
    }
}

/* for move: redo*/
int curr_to_next(Moves* moves){
    if(moves && (moves->curr) && ((moves->curr)->next))
    {
        moves->curr = (moves->curr)->next;
        return 1;
    }
    return 0;
}

/* for move: undo*/
int curr_to_prev(Moves* moves){
    if(moves && (moves->curr) && ((moves->curr)->prev))
        {
            moves->curr = (moves->curr)->prev;
            return 1;
        }
    return 0;
}

void add_new_move(Moves* moves, Board* board){
    Moves* new;
    new->next=NULL;
    new->Board_state=board;
    if(moves == NULL){ /*emptylist*/    
        new->curr= new;
        new->prev=NULL;
        moves=new;
    }
    else{ /*call only when curr is the last node*/
        (moves->curr)->next=new;
        new->prev=moves->curr;
        moves->curr=new;
    }
}