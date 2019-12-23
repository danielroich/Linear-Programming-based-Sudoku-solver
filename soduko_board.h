
#ifndef SOFTWAREPROJ_SODUKO_BOARD_H
#define SOFTWAREPROJ_SODUKO_BOARD_H

typedef struct _Board {
    int size;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
    int*** possible_values;
    int count_filled;
} Board;

int set_value(int x, int y, int value, Board* board);
int get_value(int x, int y, Board* board);

#endif 
