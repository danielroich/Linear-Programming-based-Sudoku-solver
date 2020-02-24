#include "stack_backtrack_logic.h"
#include "stack.h"
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

BacktrackState prepare_empty_state(Board* board, int board_size, int cur_x, int cur_y) {
    int next_x = get_next_row(board,cur_x,cur_y);
    int next_y = get_next_column(board,cur_y);
    int possible_values_size =0;
    int* possible_values = (int*)calloc(board_size, sizeof(int));
    BacktrackState cur_state = {next_x, next_y, possible_values_size, possible_values, 0, 1};
    return cur_state;
}

int stack_based_back_track(Board* board) {
    int i;
    int possible_values_size;
    int checked_value;
    int x = 0;
    int y = 0;
    int counter = 0;
    int board_size = board->num_of_columns*board->num_of_rows;
    Stack* stack = createStack(board_size);
    int* possible_values;
    BacktrackState cur_state = {x,y,possible_values_size, possible_values, 1};

    do {
        /*If this statement is true we have covered all the boared with values
        this indicates we have placed the entire boared with values in have finished solving it */
        if (cur_state.row == board_size) {
            ++counter;
            cur_state = pop(stack);
            continue;
        }

        if (get_value(x,y,board,0) != BOARD_NULL_VALUE) {

            if (cur_state.is_default)
            {
                cur_state.is_default = 0;
                push(stack, cur_state);
                cur_state = prepare_empty_state(board, board_size, cur_state.row, cur_state.column);
            }
            else {
                cur_state = pop(stack);
            }
            
            continue;
        }

        if (cur_state.is_default)
        {
            cur_state.possible_values_size = get_possible_values(board, cur_state.row, cur_state.column, cur_state.possible_values);
        }

        /* if not default stack frame, erase the curr value to replace it */
        else {
            erase_value(x,y,board);
        }

        /* can still try values in this square */
        if (cur_state.loop_index < cur_state.possible_values_size)
        {
             if (i == (possible_values_size - 1)) {
                checked_value = get_single_possible_value(possible_values,board_size);
            }
            else {
                checked_value = get_next_attampted_value(possible_values, possible_values_size - i, 1,
                                                        board_size);
            }
            set_value(x, y,checked_value,board);

            cur_state.is_default = 0;
            ++cur_state.loop_index;
            push(stack,cur_state);
            cur_state = prepare_empty_state(board, board_size, x, y);
        }

        /* tried all values in this square */ 
        else {
            cur_state = pop(stack);
        }
    } while(!isEmpty(stack));
    
    free(stack->items);
    free(stack);
    /* check that the inner fields in items are cleaned */
}
