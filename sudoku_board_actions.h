
#ifndef EX3_SUDOKU_BOARD_ACTIONS_H
#define EX3_SUDOKU_BOARD_ACTIONS_H

#include "sudoku_board.h"
#include "moves.h"

int solve(Board* board, char* path);
int edit(Board* board, char* path);
void mark_errors(Board* board, int is_mark);
void print_board(Board* board);
int set_value_user(int x, int y, int value, Board* board);
void validate_board(Board* board);

int undo(Board* board, Moves* moves);
int redo(Board* board, Moves* moves);
int save(Board* board, char* path);
void hint(int x, int y, Board* board);

int number_solutions(Board* board);
int autofill(Board* board);
void reset(Moves* moves, Board* board);
void exit_game(Board* board);

void restart(Board* board);
void seed(int seed);
int is_winner(Board* board);

#endif
