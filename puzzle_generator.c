#include "sudoku_board.h"
#include "backtracking_core_logic.h"
#include <stdlib.h>
#include "2d_array_utils.h"

int generate_puzzle(Board* board, int fixed_cells) {
    int i ;
    int j;
    int selected_row;
    int selected_column;
    int size = board->num_of_columns * board->num_of_rows;
    int **fixed_board = create_2d_array(size);
    back_track(board,0);

    copy_board_values(board->solved_board, board->cur_board, size);

    while(fixed_cells != 0 ) {
        selected_column = rand() % size;
        selected_row = rand() % size;


        if (fixed_board[selected_row][selected_column] == BOARD_NULL_VALUE) {
            --fixed_cells;
            fixed_board[selected_row][selected_column] = 1;
        }
    }

    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            if (fixed_board[i][j] == BOARD_NULL_VALUE) {
                erase_value(i,j,board);
            }
        }
    }

    copy_board_values(board->fixed_board, board->cur_board, size);
    free_2d_array(fixed_board, size);

    return 1;
}
