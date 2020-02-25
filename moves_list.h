#ifndef MOVES_LIST_H
#define MOVES_LIST_H

#include "sudoku_board.h"

typedef struct _Moves {
    struct _Moves* prev;
    struct _Moves* curr;
    struct _Moves* next;
    Board* Board_state;
} Moves;

void clean_nexts(Moves* moves);
void back_to_first_move(Moves* moves);
int curr_to_next(Moves* moves);
int curr_to_prev(Moves* moves);
void add_new_move(Moves* moves, Board* board);

#endif 
