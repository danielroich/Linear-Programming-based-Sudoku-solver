#include "sudoku_board.h"
#include <math.h>

int const BOARD_NULL_VALUE = 0;

/* 0<=x,y<=row*col-1 */
int get_value(int x, int y, Board* board){
    return (board->cur_board)[x][y];
}

int value_in_row(int row, int value, Board* board){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
         if(get_value(row,i,board) == value)
            return 1;
    }
    return 0;
}

int value_in_col(int col, int value, Board* board){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
         if(get_value(i,col,board) == value)
            return 1;
    }
    return 0;
}

int value_in_square(int row, int col, int value, Board* board){
    int i,j;
    int top_left_corner_row = floor(row/board->num_of_rows)*board->num_of_rows; 
    int top_left_corner_col = floor(col/board->num_of_columns)*board->num_of_columns; 
    for(i= top_left_corner_row; i<top_left_corner_row+board->num_of_rows; i++){
        for(j= top_left_corner_col; j<top_left_corner_col+board->num_of_columns; j++){
            if(get_value(i,j,board) == value)
                return 1;
        }
    }
    return 0;
}

int erase_value(int x, int y, Board* board) {

    if (board->cur_board[x][y] != BOARD_NULL_VALUE) {
        board->count_filled--;
    }

    board->cur_board[x][y] = BOARD_NULL_VALUE;
    return 1;
}

/* 0<=x,y<=row*col-1 */
int set_value(int x, int y, int value, Board* board){
    if((value_in_row(x,value,board) || value_in_col(y,value,board) || value_in_square(x,y,value,board) ))
        return 0;     
    board->cur_board[x][y] = value;
    board->count_filled++;
    return 1;
}

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