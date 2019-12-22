#include <stdio.h>
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
