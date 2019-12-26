#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"

int test_add_val_to_empty_board(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);

    set_value(0,0,3,board);

    answer =  board->cur_board[0][0] == 3;
    free_board(board, rows, columns);
    return answer;
}

int main() {

    printf("%d",test_add_val_to_empty_board(3,3));
    return 0;
}