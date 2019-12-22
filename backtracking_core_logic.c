
#include "soduko_board.h"

Board* back_track(Board* board, int is_deterministic) {
    if (is_deterministic == 0)
    {
       return deterministic_back_tracking(board);
    }
    
    return randomized_back_tracking(board);
}

Board* deterministic_back_tracking(Board* board) {
    int** cur_board = board -> cur_board;
    int board_size = board->size;
}

Board* randomized_back_tracking(Board* board) {
    
}