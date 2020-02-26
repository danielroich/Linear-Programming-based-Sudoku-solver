#include "sudoku_board.h"
#include <stdio.h>
#include "2d_array_utils.h"
#include <math.h>
#include <stdlib.h>

int const BOARD_NULL_VALUE = 0;

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

int is_legal(int x, int y, int value, Board* board, int is_fix){
    if((value_in_row(x,value,board,is_fix) || value_in_col(y,value,board,is_fix) || value_in_square(x,y,value,board,is_fix) ))
        return 0;
    return 1;
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

void set_value_without_check(int x, int y, int value, Board* board){
    board->cur_board[x][y] = value;    
    board->count_filled++;
}

int create_empty_board(Board* board, int rows, int columns) {
    int size = rows * columns;
    board->num_of_columns = columns;
    board->num_of_rows = rows;
    board->cur_board  = create_2d_array(size);
    board->fixed_board  = create_2d_array(size);
    board->solved_board  = create_2d_array(size);
    board->mode = INIT;
    board->mark_errors = 1; 
    return 1;
}

void copy_board(Board* from_board,Board* to_board){
    int size = from_board->num_of_columns * from_board->num_of_rows;
    /*assmue  allocate same sizes?*/
    to_board->mode = from_board->mode;
    to_board->mark_errors = from_board->mark_errors; 
    copy_board_values(to_board->cur_board,from_board->cur_board,size);
    copy_board_values(to_board->fixed_board,from_board->fixed_board,size);
    copy_board_values(to_board->solved_board,from_board->solved_board,size);
}

void free_board(Board* board){
    int size = (board->num_of_rows)*(board->num_of_columns);
    free_2d_array(board->solved_board,size);
    free_2d_array(board->fixed_board,size);
    free_2d_array(board->cur_board,size);
    free(board);
}

int is_erroneous_cell(Board* board,int row, int col){
    int successed;
    int value;
    if(board->cur_board[row][col] != BOARD_NULL_VALUE){
        value = get_value(row,col,board,0);
        erase_value(row,col,board);
        successed = set_value(row,col,value,board,0);
        if(successed == 0){
            set_value_without_check(row,col,value,board);
            return 1;
        }
    }
    return 0;
}

int is_erroneous_board(Board* board){
    int i, j;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            if(is_erroneous_cell(board,i,j))
                return 1;
        }
    }
    return 0;
}

int is_filled(Board* board){
    int size = (board->num_of_rows)*(board->num_of_columns);
    if(board->count_filled == size*size){
        return 1;
    }
    return 0;
}

void print_diff(Board* before, Board* after){
    int i, j, before_val, after_val;
    int size = (before->num_of_rows)*(before->num_of_columns);
    /* mode cant change, solve/edit clean moves. therefore, same sizes*/
    if(before->mark_errors != after->mark_errors){
        printf("mark_errors parameter cheanged from %d to %d",before->mark_errors,after->mark_errors);
    }
    else{
        for (i=0; i<size; i++){
            for (j=0; j<size; j++){
                before_val = get_value(i,j,before,0);
                after_val = get_value(i,j,after,0);
                if(before_val != after_val){
                    if(before_val == BOARD_NULL_VALUE){
                        before_val = 0;
                    }
                    if(after_val == BOARD_NULL_VALUE){
                        after_val = 0;
                    }
                    printf("cell (%d,%d) changed from %d to %d",j+1,i+1,before_val,after_val);
                }
            }
        }
    }
}

int single_possible_value(int row, int col, Board* board){
    int i,value;
    int count = 0;
    int size = board->num_of_columns * board->num_of_rows;
    for(i = 1; i<=size; i++){
        if(is_legal(row,col,i,board,0)){
            count++;
            value = i;
        }
        if(count>1)
            break;
    }
    if(count != 1){
        return 0;
    }
    return value;
}