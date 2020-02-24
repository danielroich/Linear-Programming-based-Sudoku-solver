#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>

int test_add_val_at_start_to_empty_board(int rows, int columns) {
    int answer;
    Board* board = (Board*) malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);

    set_value(0,0,3,board);

    answer =  board->cur_board[0][0] == 3;
    /*free_board(board, rows, columns);*/
    return answer;
}

int test_add_val_to_middle_to_empty_board(int rows, int columns) {
    int answer;
    Board* board = (Board*) malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);

    set_value(3,7,2,board);

    answer =  board->cur_board[3][7] == 2;
    /*free_board(board, rows, columns);*/
    return answer;
}

/*
int main() {

    printf("%s result: %d \n", "test_add_val_to_middle_to_empty_board", test_add_val_to_middle_to_empty_board(3,3));
    printf("%s result: %d \n", "test_add_val_at_start_to_empty_board", test_add_val_at_start_to_empty_board(3,3));

    return 0;
}*/