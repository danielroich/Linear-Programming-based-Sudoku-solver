#include "moves.h"
#include "stdio.h"
#include "stdlib.h"

void free_node(Moves* node){
    free_board(node->Board_state);
    free(node->next);
    free(node->prev);
    free(node);
}

/* for moves: solve, edit */
void clean_list(Moves* moves){
    back_to_first_move(moves);
    Moves* node = moves;
    while(node){
        Moves* next = node->next;
        free_node(node);
        node = next;
    }
}

/* for moves: set, autofill, generate, guess */
void clean_nexts(Moves* moves){
    Moves* node = moves;
    if(node){
        node=node->next;
    }
    while(node){
        Moves* next = node->next;
        free_node(node);
        node = next;
    }
}

/* for move: reset */
void back_to_first_move(Moves* moves){
    if(moves){
        while(moves->prev)
        {
            moves = moves->prev;
        }
    }
}

/* for move: redo*/
int curr_to_next(Moves* moves){
    if(moves  && (moves->next))
    {
        moves = moves->next;
        return 1;
    }
    return 0;
}

/* for move: undo*/
int curr_to_prev(Moves* moves){
    if(moves && (moves->prev))
        {
            moves = moves->prev;
            return 1;
        }
    return 0;
}

void add_new_move(Moves* moves, Board* board){
    Moves* new_node =(Moves*)malloc(sizeof(Moves));
    Board* node_board = (Board*) malloc((sizeof(Board)));
    if(new_node==NULL || node_board==NULL){
        printf("Error: malloc has failed\n");
        /*TODO: free game*/
    }

    copy_board(board,new_node->Board_state);
    new_node->next=NULL;

    if(moves == NULL){ /*emptylist*/    
        new_node->prev=NULL;
    }
    else{ /*call only when moves is the last node*/
        moves->next=new_node;
        new_node->prev=moves;
    }
    moves=new_node;

}

