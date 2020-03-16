

#ifndef EX3_BACKTRACKING_CORE_LOGIC_H
#define EX3_BACKTRACKING_CORE_LOGIC_H

#include "sudoku_board.h"

/* This functions tries to solve the sudoku board by backtracking using recursion, Not used in LP and Project
 Returns 1 if successful and 0 otherwise */
int back_track(Board* board, int is_deterministic);


#endif
