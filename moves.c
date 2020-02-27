#include "moves.h"
#include "stdio.h"
#include "stdlib.h"


void free_node(Move* node){
    if(node->Board_state != NULL)
        free_board(node->Board_state);
    free(node->next);
    free(node->prev);
    free(node);
}

/* for move: reset */
void back_to_first_move(Curr_move move){
    if(move && (*move)){
        while((*move)->prev)
        {
            (*move) = (*move)->prev;
        }
    }
}

/* for move: redo*/
int curr_to_next(Curr_move move){
    if(move && (*move) && (*move)->next)
    {
        (*move) = (*move)->next;
        return 1;
    }
    return 0;
}

/* for move: undo*/
int curr_to_prev(Curr_move move){
    if(move && (*move) && (*move)->prev)
    {
        (*move) = (*move)->prev;
        return 1;
    }
    return 0;
}

/* for moves: solve, edit */
void clean_list(Curr_move move){
    back_to_first_move(move);
    clean_nexts(move);
    if(move && *move)
        free_node(*move);
}

/* for moves: set, autofill, generate, guess */
void clean_nexts(Curr_move move){
    Move* next_node;
    Curr_move next_move;
    if(move && *move){
        next_move = &((*move)->next);
        if(next_move){
            while(*next_move){
                next_node = (*next_move)->next;
                free_node((*next_move));
                (*next_move) = next_node;
            }
        } 
    }      
}

void add_new_move(Curr_move move, Board* board){
    Move* new_node =(Move*)malloc(sizeof(Move));
    
    if(new_node==NULL){
        printf("Error: malloc has failed\n");
        /*TODO: free game*/
    }

    new_node->Board_state = (Board*) malloc((sizeof(Board)));
    create_empty_board(new_node->Board_state,board->num_of_rows,board->num_of_columns);
    copy_board(board,new_node->Board_state);
    new_node->next=NULL;

    if((*move) == NULL){ /*emptylist*/    
        new_node->prev=NULL;
    }
    else{ /*call only when moves is the last node*/
        (*move)->next=new_node;
        new_node->prev=(*move);
    }
    *move=new_node;
}