
#ifndef EX3_SUDOKU_BOARD_ACTIONS_H
#define EX3_SUDOKU_BOARD_ACTIONS_H

#include "backtracking_core_logic.h"
#include "sudoku_board.h"
#include "puzzle_generator.h"

void solve(Board* board, char* path);
void edit(Board* board, char* path);
void mark_errors(Board* board, int is_mark);
void print_board(Board* board);
int set_value_user(int x, int y, int value, Board* board);
void validate_board(Board* board);

void save(Board* board, char* path);
void hint(int x, int y, Board* board);

int number_of_solutions(Board* board);

void restart(Board* board);
void exit_game(Board* board);

void seed(int seed);
int is_filled(Board* board);

#endif
