
/* typedef board struct.
boards basic functions, memory (create, free, copy)
erroneous check, winner check*/

#ifndef SOFTWAREPROJ_SUDOKU_BOARD_H
#define SOFTWAREPROJ_SUDOKU_BOARD_H

extern int const BOARD_NULL_VALUE;

typedef enum _Mode {
    INIT,
    EDIT,
    SOLVE
} Mode;

typedef struct _Board {
    int num_of_rows; /*in block*/
    int num_of_columns; /*in block*/ 
    int count_filled;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
    int mark_errors;
    Mode mode;
} Board;

int get_value(int x, int y, Board* board, int is_fix);
int is_legal(int x, int y, int value, Board* board, int is_fix);
int set_value(int x, int y, int value, Board* board, int is_fix);
int erase_value(int x, int y, Board* board);
void set_value_without_check(int x, int y, int value, Board* board);
int create_empty_board(Board* board, int rows, int columns);
void copy_board(Board* from_board,Board* to_board);
void free_board(Board* board);
int is_erroneous_cell(Board* board,int row, int col);
int is_erroneous_board(Board* board);
int is_filled(Board* board);
void print_diff(Board* before, Board* after);
int single_possible_value(int row, int col, Board* board);
int is_winner(Board* board);

#endif 
