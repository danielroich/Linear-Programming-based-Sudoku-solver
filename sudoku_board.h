
#ifndef SOFTWAREPROJ_SUDOKU_BOARD_H
#define SOFTWAREPROJ_SUDOKU_BOARD_H

int const BOARD_NULL_VALUE = 0;

typedef struct _Board {
    int num_of_rows; /*in block*/
    int num_of_columns; /*in block*/ 
    int count_filled;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
} Board;

int set_value(int x, int y, int value, Board* board);
int get_value(int x, int y, Board* board);
int erase_value(int x, int y, Board* board);
int create_empty_board(Board* board, int rows, int columns);

#endif 
