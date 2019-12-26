#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "backtracking_core_logic.h"

int test_free_board_deterministic_backtrack(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);

    back_track(board, 1);

    answer =  board->cur_board[0][0] == 3;
    free_board(board, rows, columns);
    return answer;
}

int main() {

    printf("%d",test_free_board_deterministic_backtrack(3,3));
    return 0;
}