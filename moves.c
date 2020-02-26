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
    Moves* node = moves;
    back_to_first_move(node);
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
    
    if(new_node==NULL){
        printf("Error: malloc has failed\n");
        /*TODO: free game*/
    }

    new_node->Board_state = (Board*) malloc((sizeof(Board)));
    create_empty_board(new_node->Board_state,board->num_of_rows,board->num_of_columns);
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
