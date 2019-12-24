//
// Created by Daniel on 12/21/2019.
//

#ifndef EX3_BACKTRACKING_CORE_LOGIC_H
#define EX3_BACKTRACKING_CORE_LOGIC_H

#include "soduko_board.h"
#include "soduko_board_actions.h"

// This functions tries to solve the sudoku board by backtracking
// Returns 1 if successful and 0 otherwise
int back_track(Board* board, int is_deterministic);


#endif //EX3_BACKTRACKING_CORE_LOGIC_H
