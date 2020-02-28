
#ifndef EX3_LP_H
#define EX3_LP_H

#include "sudoku_board.h"

int validate_ILP(Board* board);
int hint_ILP(Board *board, int row, int column);
int guess_LP(Board *board, int row, int column, double threshold);

#endif
