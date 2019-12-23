#include "soduko_board.h"

/* 1<=x,y<=size*/
int get_value(int x, int y, Board* board){
    return (board->cur_board)[x-1][y-1];
}

int value_in_row(int row, int value, Board* board){
    int i;
    for (i=0; i<(board->size); i++){
         if(get_value(row,i+1,board) == value)
            return 1;
    }
    return 0;
}

int value_in_col(int col, int value, Board* board){
    int i;
    for (i=0; i<(board->size); i++){
         if(get_value(i+1,col,board) == value)
            return 1;
    }
    return 0;
}

int value_in_square(int row, int col, int value, Board* board){
    int i,j;
    int size_square = sqrt(board->size);
    int top_left_corner_row = floor(row/size_square)*size_square; 
    int top_left_corner_col = floor(col/size_square)*size_square; 
    for(i= top_left_corner_row; i<(top_left_corner_row +size_square); i++){
        for(j= top_left_corner_col; i<(top_left_corner_col +size_square); j++){
            if(get_value(i+1,j+1,board) == value)
                return 1;
        }
    }
    return 0;
} 

int set_value(int x, int y, int value, Board* board){
    if((value_in_row(x,value,board) +  value_in_col(y,value,board) + value_in_square(x-1,y-1,value,board) ) != 0){
        return 0;     
    }
    else{
        board->cur_board[x][y] = value;
        board->count_filled++;
        return 1;
    }
}

