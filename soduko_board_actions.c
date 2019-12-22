#include <stdio.h>
#include "soduko_board_actions.h"
#include <math.h>

void print_board(Board* board){
    int size_square = sqrt(board->size);
    int i = 0, j = 0, value;
    for(int a = 0; a < size_square; a++){
        printf("----------------------------------\n");
        printnf("|");
        for(i = 0; i < size_square; i++){
            for(j = 0; j < size_square; j++){
                value = get_value(i,j,board);
                if(board->fixed_board[i][j] != 0){
                    printf(".%d",value);
                }
                else{
                    if(board->cur_board[i][j] != 0)
                        printf(" %d",value);
                    else
                        printf("  ",value);
                }   
            }
            printnf("|\n");
        }
    }
    printf("----------------------------------\n");
}
