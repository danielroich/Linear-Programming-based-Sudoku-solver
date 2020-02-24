#include "sudoku_board.h"
#include "2d_array_utils.h"
#include <math.h>

/* all functions in this file get 0<=x,y<=row*col-1 */
/* if is_fix == 1 value from fixed_board else from cur*/

int get_value(int x, int y, Board* board, int is_fix){
    if(is_fix==0){
        return (board->cur_board)[x][y];
    }
    return (board->fixed_board)[x][y];
}

/* return 1 if value was found in row*/
int value_in_row(int row, int value, Board* board, int is_fix){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
         if(get_value(row,i,board,is_fix) == value)
            return 1;
    }
    return 0;
}

/* return 1 if value was found in col*/
int value_in_col(int col, int value, Board* board,int is_fix){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
         if(get_value(i,col,board,is_fix) == value)
            return 1;
    }
    return 0;
}

/* return 1 if value was found in square*/
int value_in_square(int row, int col, int value, Board* board,int is_fix){
    int i,j;
    int top_left_corner_row = floor(row/board->num_of_rows)*board->num_of_rows; 
    int top_left_corner_col = floor(col/board->num_of_columns)*board->num_of_columns; 
    for(i= top_left_corner_row; i<top_left_corner_row+board->num_of_rows; i++){
        for(j= top_left_corner_col; j<top_left_corner_col+board->num_of_columns; j++){
            if(get_value(i,j,board,is_fix) == value)
                return 1;
        }
    }
    return 0;
}

int set_value(int x, int y, int value, Board* board,int is_fix){
    if(is_legal(x,y,value,board,is_fix)==0){
        return 0;}     
    board->cur_board[x][y] = value;
    board->count_filled++;
    return 1;
}

int erase_value(int x, int y, Board* board) {

    if (board->cur_board[x][y] != BOARD_NULL_VALUE) {
        board->count_filled--;
    }

    board->cur_board[x][y] = BOARD_NULL_VALUE;
    return 1;
}

int create_empty_board(Board* board, int rows, int columns) {
    int size = rows * columns;
    board->num_of_columns = columns;
    board->num_of_rows = rows;
    board->cur_board  = create_2d_array(size);
    board->fixed_board  = create_2d_array(size);
    board->solved_board  = create_2d_array(size);
    board->mode = INIT;

    return 1;
}

int is_legal(int x, int y, int value, Board* board, int is_fix){
    if((value_in_row(x,value,board,is_fix) || value_in_col(y,value,board,is_fix) || value_in_square(x,y,value,board,is_fix) ))
        return 0;
    return 1;
}