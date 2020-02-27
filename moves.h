#ifndef MOVES_H
#define MOVES_H

#include "sudoku_board.h"

typedef struct _Move {
    struct _Move* prev;
    struct _Move* next;
    Board* Board_state;
} Move;

typedef Move** Curr_move;

void back_to_first_move(Curr_move move);
int curr_to_next(Curr_move move);
int curr_to_prev(Curr_move move);
void clean_list(Curr_move move);
void clean_nexts(Curr_move move);
void add_new_move(Curr_move move, Board* board);

#endif 
