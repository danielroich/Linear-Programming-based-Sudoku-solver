
#ifndef SOFTWAREPROJ_SUDOKU_BOARD_H
#define SOFTWAREPROJ_SUDOKU_BOARD_H

int const BOARD_NULL_VALUE;

typedef struct _Board {
    int num_of_rows; /*in block*/
    int num_of_columns; /*in block*/ 
    int count_filled;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
} Board;

typedef struct _Point {
    int x;
    int y;
} Point;

int set_value(int x, int y, int value, Board* board);
int get_value(int x, int y, Board* board);

#endif 
