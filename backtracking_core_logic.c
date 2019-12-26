
#include "sudoku_board.h"
#include <math.h>
#include <time.h>

// TODO: Check for allocated points and free them
// TODO: determine different kind of consts
int get_next_row(const Board* board, int cur_row, int cur_column) {
    int new_row = cur_row;
    int size = board->num_of_rows*board->num_of_columns;

    if (cur_column == (size-1))
    {
        ++new_row;
    }

    return new_row;
}

int get_next_column(const Board* board, int cur_row, int cur_column) {
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

int back_track(Board* board, int is_deterministic) {
    int is_sol_found;
    int x_start = 0;
    int y_start = 0;

    is_sol_found = rec_back_tracking(board, x_start, y_start, &is_deterministic);

    return is_sol_found;
}

int rec_back_tracking(Board* board, int x, int y, const int* is_deterministic) {
    int i;
    int possible_values_size;
    int* possible_values;
    int checked_value;
    int is__solving_successful = 0;
    int next_x = get_next_row(board,x,y);
    int next_y = get_next_column(board,x,y);

    // If this statement is true we have covered all the boared with values
    // this indicates we have placed the entire boared with values in have finished solving it
    if (x == board->num_of_rows * board->num_of_columns)
        return 1;

    if (get_value(x,y,board) != BOARD_NULL_VALUE)
    {
        is__solving_successful =  rec_back_tracking(board, next_x, next_y, is_deterministic);
    }
    
    else {

        possible_values_size = get_possible_values(board, x, y, possible_values);

        for (i = 0; i < possible_values_size; i++)
        {
            checked_value = get_next_attampted_value(possible_values, possible_values_size - i, is_deterministic);

            set_value(x, y,checked_value,board);
            
            is__solving_successful = rec_back_tracking(board, next_x, next_y, is_deterministic);
            
            if (is__solving_successful)
                break;
            
            set_value_point(x, y, BOARD_NULL_VALUE, board);
        }
        
        // At this point we are sure that the board cannot be solved by the given board to the func
        // So we restore the current cell back to null and return false
        free(possible_values);
        return is__solving_successful;
    }
    
    // TODO: free tried values
}

// returns size and updates possible_values
int get_possible_values(const Board* board, int x, int y, int* possible_values) {
    int i;
    int counter = 0;
    int possible_values_num;

    // if the board contains value in this point, return error
    if (get_value(x, y, board) != BOARD_NULL_VALUE)
    {
        return -1;
    }

    possible_values_num = board->num_of_columns*board->num_of_rows;

    for (i = 1; i < possible_values_num + 1; i++)
    {
        if(set_value(x, y,i,board)) {
            ++counter;
            possible_values = (int*) realloc(possible_values, sizeof(int) * counter);
            // put the number in the array
        }
        set_value_point(point,BOARD_NULL_VALUE,board);
    }

    return counter;
}

int get_next_attampted_value(int* possible_values, int possible_values_size, int* is_deterministic) {

    int chosen_val;
    int rand_index;
    int* new_possible_values = (int*) malloc((possible_values_size - 1) * sizeof(int));

    if (*is_deterministic)
    {
        chosen_val = possible_values[0];
        memcpy(new_possible_values, ++possible_values, (possible_values_size - 1) * sizeof(int));
    }
    else {
        rand_index = rand() % possible_values_size;
        chosen_val = possible_values[rand_index];
        memcpy(new_possible_values, possible_values, rand_index * sizeof(int));
        memcpy(new_possible_values, possible_values + rand_index + 1, (possible_values_size - rand_index - 1) * sizeof(int));
    }


    free(possible_values);
    possible_values = new_possible_values;
    return chosen_val;
}