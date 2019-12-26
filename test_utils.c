
#include "sudoku_board.h"
#include <stdlib.h>

int create_empty_board(Board* board, int rows, int columns) {
    int i;
    int **cur_board;
    int **fixed_board;
    int size = rows * columns;
    board->num_of_columns = columns;
    board->num_of_rows = rows;
    cur_board = (int **)malloc(size * sizeof(int*));
    for (i=0; i<size; i++)
        cur_board[i] = (int *)calloc(size ,sizeof(int));
    fixed_board = (int **)malloc(size * sizeof(int*));
    for (i=0; i<size; i++)
        fixed_board[i] = (int *)calloc(size ,sizeof(int));
    board->cur_board = cur_board;
    board->fixed_board = fixed_board;

    return 1;
}

int free_board(Board* board) {
    int i;
    int size = board->num_of_rows * board->num_of_columns;
    for (i=0; i<size; i++) {
        free(board->cur_board[i]);
        free(board->fixed_board[i]);
    }

    free(board->cur_board);
    free(board->fixed_board);
    free(board);

    return 1;
}
