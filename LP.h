
#ifndef EX3_LP_H
#define EX3_LP_H

#include "sudoku_board.h"
#include "optional_cell_values.h"

int validate_ILP(Board* board);
int hint_ILP(Board *board, int row, int column);
int guess_LP(Board *board, int row, int column, float threshold);
OptionalCellValues* get_values_for_cell(Board* board, int row, int column);
void fill_board(Board* board, int is_integer, float threshold);

#endif
