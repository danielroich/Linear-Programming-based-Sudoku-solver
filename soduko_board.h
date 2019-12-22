
#ifndef SOFTWAREPROJ_SODUKO_BOARD_H
#define SOFTWAREPROJ_SODUKO_BOARD_H

typedef struct _Board {
    int** solved_board;
    int** cur_board;
    int*** possible_values;
} Board;


#endif 
