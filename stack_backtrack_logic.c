#include "stack_backtrack_logic.h"
#include "stack.h"
#include <stdlib.h>
#include "backtrack_core.h"
#include "sudoku_board_actions.h"
#include <stdio.h>

#define EMPTY_STATE_INIT {0,0,0,NULL,0,1}


BacktrackState prepare_empty_state(int board_size, int cur_x, int cur_y) {
    int* possible_values = (int*)calloc(board_size, sizeof(int));
    BacktrackState cur_state = EMPTY_STATE_INIT;
    cur_state.column=cur_y;
    cur_state.row=cur_x;
    cur_state.possible_values=possible_values;
    return cur_state;
}

int stack_based_back_track(Board* board) {
    int checked_value;
    int counter = 0;
    int board_size = board->num_of_columns*board->num_of_rows;
    Stack* stack = createStack(board_size*board_size);
    BacktrackState cur_state = prepare_empty_state(board_size,0,0);

    do {
        int next_x = get_next_row(board,cur_state.row,cur_state.column);
        int next_y = get_next_column(board,cur_state.column);

        /*If this statement is true we have covered all the boared with values
        this indicates we have placed the entire boared with values in have finished solving it */
        if (cur_state.row == board_size) {
            ++counter;
            cur_state = pop(stack);
            continue;
        }

        if (get_value(cur_state.row,cur_state.column,board,1) != BOARD_NULL_VALUE) {

            if (cur_state.is_default)
            {
                cur_state.is_default = 0;
                push(stack, cur_state);
                cur_state = prepare_empty_state(board_size, next_x, next_y);
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
            erase_value(cur_state.row,cur_state.column,board);
        }

        /* can still try values in this square */
        if (cur_state.loop_index < cur_state.possible_values_size)
        {
             if (cur_state.loop_index == (cur_state.possible_values_size - 1)) {
                checked_value = get_single_possible_value(cur_state.possible_values,board_size);
            }
            else {
                checked_value = get_next_attampted_value(cur_state.possible_values, cur_state.possible_values_size - cur_state.loop_index, 1,
                                                        board_size);
            }
            set_value(cur_state.row, cur_state.column,checked_value,board,0);

            cur_state.is_default = 0;
            ++cur_state.loop_index;
            push(stack,cur_state);
            cur_state = prepare_empty_state(board_size, next_x, next_y);
        }

        /* tried all values in this square */ 
        else {
            cur_state = pop(stack);
        }
    } while(cur_state.row != -1);
    
    free(stack->items);
    free(stack);
    /* check that the inner fields in items are cleaned */

    return counter;
}
