#include "soduko_board.h"

/* 0<=x,y<=size-1 */
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

/* fix!*/
int value_in_square(int row, int col, int value, Board* board){
    int i,j;
    int size_square = sqrt(board->size);
    int top_left_corner_row = floor(row/size_square)*size_square; 
    int top_left_corner_col = floor(col/size_square)*size_square; 
    for(i= top_left_corner_row; i<(top_left_corner_row +size_square); i++){
        for(j= top_left_corner_col; i<(top_left_corner_col +size_square); j++){
            if(get_value(i,j,board) == value)
                return 1;
        }
    }
    return 0;
} 

/* 0<=x,y<=size-1 */
int set_value(int x, int y, int value, Board* board){
    if((value_in_row(x,value,board) || value_in_col(y,value,board) || value_in_square(x,y,value,board) ))
        return 0;     
    board->cur_board[x][y] = value;
    board->count_filled++;
    return 1;
}

