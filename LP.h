
#ifndef EX3_LP_H
#define EX3_LP_H

#include "sudoku_board.h"
#include "optional_cell_values.h"

int validate_ILP(Board* board);
OptionalCellValues* get_value_for_cell(Board* board, int row, int column,int is_integer);
void fill_board(Board* board, int is_integer, float threshold);

#endif
