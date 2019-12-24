
#include "soduko_board.h"
#include <math.h>
#include <time.h>

// TODO: Check for allocated points and free them
Point* get_next_point(const Board* board, const Point* point) {
    int new_x;
    int new_y;
    Point* next_point;

    if (point->y == (board->num_of_columns-1))
    {
        new_y = 0;
        new_x = (point-> x) + 1;
    }
    else {
        new_y = (point-> y) + 1;
        new_x = point-> x;
    }
    
    next_point = (Point*){new_x, new_y};

    return next_point;
}

int back_track(Board* board, int is_deterministic) {
    int i;
    int is_sol_found;
    Point* starting_point = {0,0};

    is_sol_found = rec_back_tracking(board, starting_point, &is_deterministic);

    free(starting_point);
    return is_sol_found;
}

int rec_back_tracking(Board* board, Point* point, int* is_deterministic) {
    int i;
    int possible_values_size;
    int* possible_values;
    int checked_value;
    int is__solving_successful = 0;
    Point* next_point = get_next_point(board,point);

    // If this statement is true we have covered all the boared with values
    // this indicates we have placed the entire boared with values in have finished solving it
    if (point->x == board->num_of_rows * board->num_of_columns)
        return 1;

    if (get_value_point(point,board) != BOARD_NULL_VALUE)
    {
        is__solving_successful =  rec_back_tracking(board, next_point, is_deterministic);
    }
    
    else {

        possible_values_size = get_possible_values(board,point, possible_values);

        for (i = 0; i < possible_values_size; i++)
        {
            checked_value = get_next_attampted_value(possible_values, possible_values_size - i, is_deterministic);

            set_value_point(point,checked_value,board);
            
            is__solving_successful = rec_back_tracking(board, next_point, is_deterministic);
            
            if (is__solving_successful)
                break;
            
            set_value_point(point, BOARD_NULL_VALUE, board);
        }
        
        // At this point we are sure that the board cannot be solved by the given board to the func
        // So we restore the current cell back to null and return false
        free(possible_values);
        free(next_point);
        return is__solving_successful;
    }
    
    // TODO: free tried values
}

// returns size and updates possible_values
int get_possible_values(const Board* board, const Point* point, int* possible_values) {
    int i;
    int counter = 0;
    int possible_values_num;

    // if the board contains value in this point, return error
    if (get_value_point(point, board) != BOARD_NULL_VALUE)
    {
        return -1;
    }
    

    //TODO: What happend when the board isn't 9x9
    possible_values_num = sqrt(board->num_of_columns);

    for (i = 1; i < possible_values_num + 1; i++)
    {
        if(set_value_point(point,i,board)) {
            ++counter;
            possible_values = (int*) realloc(possible_values, sizeof(int) * counter);
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