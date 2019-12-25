#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>

int initialize_empty_board(Board *board, int rows, int columns) {
    int i;
    int **cur_board;
    int **fixed_board;
    board->num_of_columns = columns;
    board->num_of_rows = rows;
    cur_board = (int **)malloc(rows * sizeof(int*)); 
    for (i=0; i<rows; i++) 
         cur_board[i] = (int *)calloc(columns ,sizeof(int)); 
    fixed_board = (int **)malloc(rows * sizeof(int*)); 
    for (i=0; i<rows; i++) 
         fixed_board[i] = (int *)calloc(columns ,sizeof(int)); 
    board->cur_board = cur_board;
    board->fixed_board = fixed_board;
    
    return 1;
}

int test_add_val_to_empty_board(int rows, int columns) {
    Board* board;
    initialize_empty_board(board, rows, columns);

    printf("started");
    set_value(1,1,3,board);

    return board->cur_board[0][0] == 3;
}

int main() {

    printf("tets");
    printf("%d",test_add_val_to_empty_board(9,9));
    return 0;
}