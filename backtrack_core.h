
#ifndef EX3_BACKTRACKING_CORE_BASE_H
#define EX3_BACKTRACKING_CORE_BASE_H

#include "sudoku_board.h"
#include "sudoku_board_actions.h"

int get_next_row(const Board* board, int cur_row, int cur_column);
int get_next_column(const Board* board, int cur_column);
int get_possible_values(Board* board, int x, int y, int* possible_values);
int get_next_attampted_value(int* possible_values, int possible_values_size, int is_deterministic, int size);
int get_single_possible_value(int* possible_values, int size);

#endif