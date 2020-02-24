
#ifndef SOFTWAREPROJ_backtrack_state_H
#define SOFTWAREPROJ_backtrack_state_H

typedef struct _Backtrack_state {
    int num_of_rows; /*in block*/
    int num_of_columns; /*in block*/ 
    int count_filled;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
} BacktrackState;

#endif