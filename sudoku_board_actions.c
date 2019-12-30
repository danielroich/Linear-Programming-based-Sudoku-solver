#include <stdio.h>
#include <stdlib.h>
#include "sudoku_board_actions.h"
#include <math.h>
#include <time.h>
#include "puzzle_generator.h"

void print_board(Board* board){
    int a, b, c, d;
    int row, col, value;
    for(a = 0; a < board->num_of_columns; a++){ 
        printf("----------------------------------\n"); 
        for(b = 0; b < board->num_of_rows; b++){
            row = b + a*(board->num_of_rows);
            printf("| ");
            for(c = 0; c < board->num_of_rows; c++){
                for(d = 0; d < board->num_of_columns; d++){
                    col = d + c*board->num_of_columns;
                    value = get_value(row,col,board);
                    if(board->fixed_board[row][col] != BOARD_NULL_VALUE){
                        printf(".%d ",value);
                    }
                    else{
                        if(value != BOARD_NULL_VALUE)
                            printf(" %d ",value);
                        else
                            printf("   ");
                    }
                }
                if(c != (board->num_of_rows-1))
                    printf("| ");
            }
            printf("|\n");
        }     
    }
    printf("----------------------------------\n");
}

int is_filled(Board* board){
    int size = (board->num_of_rows)*(board->num_of_columns);
    if(board->count_filled == size*size){
        return 1;
        /*From this point, all commands except exit and restart are considered invalid.*/
    }
    return 0;
}

/* assume the values of X, Y, and Z are valid and correct 
return 0 if Error or Erase
announces if game is over (full board) */
int set_value_user(int x, int y, int value, Board* board){
    if((board->fixed_board)[x-1][y-1] != BOARD_NULL_VALUE){
        printf("Error: cell is fixed\n");
        return 0;
    }
    if(value == 0){
        erase_value(x-1,y-1,board);
        print_board(board);
        return 0;
    }
    if(set_value(x-1,y-1,value,board) == 0){
            printf("Error: value is invalid\n");
            return 0;
    }
    /* else value was set and filled++ in set_value */    
    print_board(board);
    if(is_filled(board) == 1){
        printf("Puzzle solved successfully\n");
    }
    return 1;
}

/* assume that the values X, Y are valid integers in the correct range */
void hint(int x, int y, Board* board){
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

/* free memo and exit*/
void exit_game(Board* board){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    printf("Exiting...\n");
    free(&board->count_filled); 
    free(&board->num_of_columns);
    free(&board->num_of_rows);
    for (i = 0; i < size; i++) { 
        free(board->solved_board[i]);
        free(board->fixed_board[i]);
        free(board->cur_board[i]);
    }
    free(board->solved_board);
    free(board->fixed_board);
    free(board->cur_board);
    exit(0);
}

/* set BOARD_NULL_VALUE to cur/solved/fixed and count_filled = 0
call generate_puzzle with user new fixed */
void restart(Board* board){
    int fixed, i, j;
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
    /*null values board*/
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            board->cur_board[i][j]=BOARD_NULL_VALUE;
            board->solved_board[i][j]=BOARD_NULL_VALUE;
            board->fixed_board[i][j]=BOARD_NULL_VALUE;
            board->count_filled = 0;
        }
    }
    generate_puzzle(board, fixed);
    print_board(board);
}

void seed(int seed) {
    srand(seed);
}