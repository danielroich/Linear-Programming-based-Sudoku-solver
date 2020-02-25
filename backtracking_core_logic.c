#include "sudoku_board.h"
#include "2d_array_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "backtrack_core.h"
#include "sudoku_board_actions.h"

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

    if (get_value(x,y,board,0) != BOARD_NULL_VALUE)
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
            set_value(x, y,checked_value,board,0);

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
    int is_sol_found = 0;
    int x_start = 0;
    int y_start = 0;

    is_sol_found = rec_back_tracking(board, x_start, y_start, is_deterministic);

    if(is_sol_found) {
        copy_board_values(board->solved_board, board->cur_board, board->num_of_rows * board->num_of_columns);
    }
    return is_sol_found;
}


