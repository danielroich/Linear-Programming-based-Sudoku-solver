/* list of user commands*/

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
int generate(Board* board, int fill, int keep);
int undo(Board* board, Curr_move move);
int redo(Board* board, Curr_move move);
int save(Board* board, char* path);
void hint(int x, int y, Board* board);
void guess(Board* board, int row, int coulmn, float threshold);
void guess_hint(Board* board, int row, int coulmn);


int number_solutions(Board* board);
int autofill(Board* board);
void reset(Curr_move move, Board* board);
void exit_game(Board* board, Curr_move move);

void seed(int seed);

#endif
