#include "moves.h"
#include "stdio.h"
#include "stdlib.h"

/* free board and node*/
void free_node(Move* node){
    free_board((node)->Board_state);
    free(node);
}

/* for move: reset
change current move to the first node*/
void back_to_first_move(Curr_move move){
    if(move && (*move)){
        while((*move)->prev)
        {
            (*move) = (*move)->prev;
        }
    }
}

/* for move: redo
change current pointer to the next node*/
int curr_to_next(Curr_move move){
    if(move && (*move) && (*move)->next)
    {
        (*move) = (*move)->next;
        return 1;
    }
    return 0;
}

/* for move: undo
change current pointer to the next node*/
int curr_to_prev(Curr_move move){
    if(move && (*move) && (*move)->prev)
    {
        (*move) = (*move)->prev;
        return 1;
    }
    return 0;
}

/* for moves: solve, edit 
free all list of moves*/
void clean_list(Curr_move move){
    back_to_first_move(move);
    clean_nexts(move);
    if(move && *move && (*move)->Board_state)
        free_node(*move);
    *move = NULL;
}

/* for moves: set, autofill, generate, guess 
free all next nodes of the current move*/
void clean_nexts(Curr_move move){
    Move *next_node, *next_node2;
    if(move && *move){
        next_node =(*move)->next;
        while(next_node){
                next_node2 = (next_node)->next;
                free_node(next_node);
                next_node = next_node2;
        }
        (*move)->next = NULL;
    } 
}

/* for moves: solve, edit, mark_errors, set, autofill, guess, generate
add new move to the end of the list*/
void add_new_move(Curr_move move, Board* board){
    Move* new_node =(Move*)malloc(sizeof(Move));
    if(new_node==NULL){
        printf("Error: malloc has failed\n");
        /*TODO: free game*/
    }

    new_node->Board_state = (Board*) malloc((sizeof(Board)));
    if(new_node==NULL){
        printf("Error: malloc has failed\n");
        /*TODO: free game*/
    }

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