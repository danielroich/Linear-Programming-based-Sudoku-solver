#include "backtrack_core.h"
#include "2d_array_utils.h"
#include <stdlib.h>

int get_next_row(const Board* board, int cur_row, int cur_column) {
    int new_row = cur_row;
    int size = board->num_of_rows*board->num_of_columns;

    if (cur_column == (size-1))
    {
        ++new_row;
    }

    return new_row;
}

int get_next_column(const Board* board, int cur_column) {
    int new_column = cur_column;
    int size = board->num_of_rows*board->num_of_columns;

    if (cur_column == (size-1))
    {
        new_column = 0;
    }
    else {
        ++new_column;
    }

    return new_column;
}

/* returns size and updates possible_values */
int get_possible_values(Board* board, int x, int y, int* possible_values) {
    int i;
    int counter = 0;
    int possible_values_num;

    /* if the board contains value in this point, return error */
    if (get_value(x, y, board,0) != BOARD_NULL_VALUE)
    {
        return -1;
    }

    possible_values_num = board->num_of_columns*board->num_of_rows;

    for (i = 0; i < possible_values_num; i++)
    {
        if(set_value(x, y,(i+1),board,0)) {
            ++counter;
            possible_values[i] = 1;
        }
        erase_value(x,y,board);
    }

    return counter;
}

int get_next_attampted_value(int* possible_values, int possible_values_size, int is_deterministic, int size) {
    int i;
    int rand_index;
    int counter = 0;

    if (is_deterministic)
    {
        for (i = 0; i < size ; ++i) {
            if (possible_values[i] != 0) {
                possible_values[i] = 0;
                return (i + 1);
            }
        }
    }
    else {
        rand_index = rand() % possible_values_size;
        for (i = 0; i < size; ++i) {
            if (possible_values[i] == 1 && counter == rand_index) {
                possible_values[i] = 0;
                return (i+1);
            }

            if (possible_values[i] == 1) {
                ++counter;
            }
        }
    }
    return -1;
}

int get_single_possible_value(int* possible_values, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if(possible_values[i] == 1) {
            possible_values[i] = 0;
            return (i+1);
        }
    }

    return -1;
}
