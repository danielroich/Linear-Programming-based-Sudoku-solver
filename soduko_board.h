
#ifndef SOFTWAREPROJ_SODUKO_BOARD_H
#define SOFTWAREPROJ_SODUKO_BOARD_H

int const BOARD_NULL_VALUE = 0;

typedef struct _Board {
    // in block
    int num_of_rows;
    int num_of_columns;
    
    int size;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
    int count_filled;
} Board;

typedef struct _Point {
    int x;
    int y;
} Point;

int set_value(int x, int y, int value, Board* board);
int get_value(int x, int y, Board* board);
int set_value_point(Point* point, int value, Board* board);
int get_value_point(Point* point, Board* board);

#endif 
