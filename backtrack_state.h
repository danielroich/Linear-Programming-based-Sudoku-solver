
#ifndef SOFTWAREPROJ_backtrack_state_H
#define SOFTWAREPROJ_backtrack_state_H

typedef struct _Backtrack_state {
    int row;
    int column;
    int possible_values_size;
    int* possible_values;
    int loop_index;
    
    /* 1 for true */
    int is_default;

} BacktrackState;

#endif