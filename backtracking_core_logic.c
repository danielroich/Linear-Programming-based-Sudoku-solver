
#include "soduko_board.h"

Board* back_track(Board* board, int is_deterministic) {
    if (is_deterministic == 0)
    {
       return deterministic_back_tracking(board, 0, 0);
    }
    
    return randomized_back_tracking(board);
}

Board* deterministic_back_tracking(Board* board, int x, int y) {
    int i;
    int** cur_board = board -> cur_board;
    int board_size = board->size;
    int*** possible_values = board -> possible_values;

    for (i = 0; i < board_size; i++)
    {
        if (possible_values[x][y][i] == 1) {
            cur_board[x][y] = (i+1);
            advance_in_soduko(board, x, y);
        }
    }
}

Board* advance_in_soduko(Board* board, int x, int y) {

}

Board* randomized_back_tracking(Board* board) {
    
}