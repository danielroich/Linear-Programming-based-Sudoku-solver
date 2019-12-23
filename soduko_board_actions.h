//
// Created by Daniel on 12/21/2019.
//

#ifndef EX3_SODUKO_BOARD_ACTIONS_H
#define EX3_SODUKO_BOARD_ACTIONS_H

#include "backtracking_core_logic.h"
#include "soduko_board.h"
#include "puzzle_generator.h"

void print_board(Board* board);
int hint(int x, int y, Board* board);
void validate_board(Board* board);
void restart(Board* board);
void exit_game(Board* board);

#endif //EX3_
