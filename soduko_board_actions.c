#include <stdio.h>
#include <stdlib.h>
#include "soduko_board_actions.h"
#include <math.h>

/*fix!*/
void print_board(Board* board){
    int size_square = sqrt(board->size);
    int size = (board->num_of_rows)*(board->num_of_columns);
    int a, b, c, d;
    int row, col, value;
    for(a = 0; a < board->num_of_columns; a++){ 
        printf("----------------------------------\n"); 
        for(b = 0; b < board->num_of_rows; b++){
            row = b ;
            printnf("| ");
            for(c = 0; c < size_square; c++){
                for(d = 0; d < size_square; d++){
                    col = d + c*size_square;
                    value = get_value(row,col,board);
                    if(board->fixed_board[row][col] != 0){
                        printf(".%d ",value);
                    }
                    else{
                        if(board->cur_board[row][col] != BOARD_NULL_VALUE)
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

/* assume the values of X, Y, and Z are valid and correct */
int set_value_user(int x, int y, int value, Board* board){
    if((board->fixed_board)[x-1][y-1] != BOARD_NULL_VALUE){
        printf("Error: cell is fixed\n");
        return 0;
    }
    if(value == 0){
        board->cur_board[x-1][y-1] = BOARD_NULL_VALUE;
        board->count_filled--;
        print_board(board);
        return 0;
    }
    if(set_value(x-1,y-1,value,board) == 0){
            printf("Error: value is invalid\n");
            return 0;
    }
    /* else value was set and count++ in func */    
    print_board(board);
    return 1;
}

/* assume that the values X, Y are valid integers in the correct range */
int hint(int x, int y, Board* board){
    int value = board->solved_board[x-1][y-1];
    printf("Hint: set cell to %d\n",value);
}

void validate_board(Board* board){
    int valid_board = back_track(board,1); /*deterministic*/
    if(valid_board == 0)/*not vaild*/
        printf("Validation failed: board is unsolvable\n");
    else
        printf("Validation passed: board is solvable\n");
}

void exit_game(Board* board){
    printf("Exiting…\n");
    free(board); /*add!*/
    exit(0);
}

void restart(Board* board){
    int fixed;
    int size = (board->num_of_rows)*(board->num_of_columns);
    int max_fill = size*size-1;
    printf("Please enter the number of cells to fill [0-%d]:\n",max_fill);
    if(feof(stdin)){exit_game(board);}
    scanf("%d",&fixed);
    while(fixed<0 || fixed>max_fill){ /*assume the user enters a single valid integer*/
        printf("Error: invalid number of cells to fill (should be between 0 and %d)\n",max_fill);
        if(feof(stdin)){exit_game(board);}
        scanf("%d",&fixed);
    }
    generate_puzzle(board, fixed);
}

int is_filled(Board* board){
    int size = (board->num_of_rows)*(board->num_of_columns);
    if(board->count_filled == size*size){
        printf("Puzzle solved successfully\n");
        return 1;
        /*From this point, all commands except exit and restart are considered invalid.*/
    }
    return 0;
}