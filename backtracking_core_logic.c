#include "sudoku_board.h"
#include <stdlib.h>
#include "stdio.h"

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
    if (get_value(x, y, board) != BOARD_NULL_VALUE)
    {
        return -1;
    }

    possible_values_num = board->num_of_columns*board->num_of_rows;

    for (i = 0; i < possible_values_num; i++)
    {
        if(set_value(x, y,(i+1),board)) {
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

int rec_back_tracking(Board* board, int x, int y, int is_deterministic) {
    int i;
    int possible_values_size;
    int checked_value;
    int is__solving_successful = 0;
    int size = board->num_of_columns*board->num_of_rows;
    int next_x = get_next_row(board,x,y);
    int next_y = get_next_column(board,y);
    int* possible_values = (int*)calloc(size, sizeof(int));


    /*If this statement is true we have covered all the boared with values
     this indicates we have placed the entire boared with values in have finished solving it */
    if (x == board->num_of_rows * board->num_of_columns) {
        free(possible_values);
        return 1; }

    if (get_value(x,y,board) != BOARD_NULL_VALUE)
    {
        free(possible_values);
        return rec_back_tracking(board, next_x, next_y, is_deterministic);
    }

    else {

        possible_values_size = get_possible_values(board, x, y, possible_values);

        for (i = 0; i < possible_values_size; i++)
        {
            if (i == (possible_values_size - 1)) {
                checked_value = get_single_possible_value(possible_values,size);
            }
            else {
                checked_value = get_next_attampted_value(possible_values, possible_values_size - i, is_deterministic,
                                                         size);
            }
            set_value(x, y,checked_value,board);

            is__solving_successful = rec_back_tracking(board, next_x, next_y, is_deterministic);

            if (is__solving_successful)
            {
                free(possible_values);
                return 1;
            }
            erase_value(x,y,board);
        }

        /* At this point we are sure that the board cannot be solved by the given board to the func
         So we restore the current cell back to null and return false */
        free(possible_values);
        erase_value(x,y,board);
        return 0;
    }
}

int back_track(Board* board, int is_deterministic) {
    int is_sol_found;
    int x_start = 0;
    int y_start = 0;

    is_sol_found = rec_back_tracking(board, x_start, y_start, is_deterministic);

    return is_sol_found;
}


