#include <stdio.h>
#include <stdlib.h>
#include "soduko_board_actions.h"
#include <math.h>

void print_board(Board* board){
    int size_square = sqrt(board->size);
    int a, b, c, d;
    int row, col, value;
    for(a = 0; a < size_square; a++){ 
        printf("----------------------------------\n"); 
        for(b = 0; b < size_square; b++){
            row = b;
            printnf("| ");
            for(c = 0; c < size_square; c++){
                for(d = 0; d < size_square; d++){
                    col = d + c*size_square;
                    value = get_value(row,col,board);
                    if(board->fixed_board[row][col] != 0){
                        printf(".%d ",value);
                    }
                    else{
                        if(board->cur_board[row][col] != 0)
                            printf(" %d ",value);
                        else
                            printf("   ",value);
                    }
                }
                if(c != (size_square-1))
                    printnf("| ");
            }
            printnf("|\n");
        }     
    }
    printf("----------------------------------\n");
}

/* 1<=x,y<=size*/
int get_value(int x, int y, Board* board){
    return (board->cur_board)[x-1][y-1];
}

/* assume the values of X, Y, and Z are valid and correct */
int set_value(int x, int y, int value, Board* board){
    if((board->fixed_board)[x-1][y-1] != 0){
        printf("Error: cell is fixed\n");
        return 0;
    }
    if(value == 0){
        board->cur_board[x-1][y-1] = value;
        board->count_filled--;
        print_board(board);
        return 0;
    }
    if((value_in_row(x,value,board) +  value_in_col(y,value,board) + value_in_square(x-1,y-1,value,board) ) != 0){
            printf("Error: value is invalid\n");
            return 0;
    }    
    board->cur_board[x-1][y-1] = value;
    board->count_filled++;
    print_board(board);
    if(board->count_filled == (board->size)*(board->size))
        printf("Puzzle solved successfully\n");
        /*From this point, all commands except exit and restart are considered invalid.*/
    return 0;
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

/* assume that the values X, Y are valid integers in the correct range */
int hint(int x, int y, Board* board){
    int value = board->solved_board[x-1][y-1];
    printf("Hint: set cell to %d\n",value);
}

void validate_board(Board* board){
    Board* valid_board = back_track(board,1); /*deterministic*/
    if(valid_board==NULL /*not vaild*/)
        printf("Validation failed: board is unsolvable\n");
    else{
        board->solved_board = &valid_board;
        printf("Validation passed: board is solvable\n");
    }
}

void exit_game(Board* board){
    printf("Exiting…\n");
    free(board);
    exit(0);
}

void restart(Board* board){
    int fixed;
    int max_fill = ((board->size)*(board->size))-1;
    printf("Please enter the number of cells to fill [0-%d]:\n",max_fill);
    if(feof(stdin)){exit_game(board);}
    scanf("%d",&fixed);
    while(fixed<0 || fixed>max_fill){ /*assume the user enters a single valid integer*/
        printf("Error: invalid number of cells to fill (should be between 0 and %d)\n",max_fill);
        if(feof(stdin)){exit_game(board);}
        scanf("%d",&fixed);
    }
    board->count_filled = fixed;
    board->fixed_board = generate_puzzle(board->size,fixed); /*INITIALIZATION!*/
}
