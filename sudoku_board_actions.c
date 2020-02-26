#include <stdio.h>
#include <stdlib.h>
#include "sudoku_board_actions.h"
#include "backtracking_core_logic.h"
#include "puzzle_generator.h"
#include "2d_array_utils.h"
#include "files_utils.h"
#include "stack_backtrack_logic.h"
#include "moves_list.h"
#include "puzzle_generator.h"

int is_erroneous(Board* board){
    int i, j, value;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            if(board->cur_board[i][j] != BOARD_NULL_VALUE){
                value = board->cur_board[i][j];
                board->cur_board[i][j] = BOARD_NULL_VALUE; /*not clash with himself*/
                if(is_legal(i,j,value,board,0) == 0)
                    return 1;
                board->cur_board[i][j]=value;
            }
        }
    }
    return 0;
}

int is_filled(Board* board){
    int size = (board->num_of_rows)*(board->num_of_columns);
    if(board->count_filled == size*size){
        return 1;
        /*From this point, all commands except exit and restart are considered invalid.*/
    }
    return 0;
}

void seed(int seed) {
    srand(seed);
}

int is_winner(Board* board){
    /* TODO: change */
    int is_erroneous = 0;

    int size = (board->num_of_rows)*(board->num_of_columns);
    if(board->count_filled != size*size){
        return 0;
    }
    if(is_erroneous == 1)
        return 0;
    return 1;
}

/*COMMAND 17*/
/* free memo and exit*/
void exit_game(Board* board){
    int size = (board->num_of_rows)*(board->num_of_columns);
    printf("Exiting...\n");
    free_2d_array(board->solved_board,size);
    free_2d_array(board->fixed_board,size);
    free_2d_array(board->cur_board,size);
    free(board);
    exit(0);
}

/*COMMAND 1*/ 
int solve(Board* board, char* path){
    int succeeded;
    succeeded = read_file_to_board(board,path,1);
    if(succeeded == 0){
        printf("Error: invalid file\n");
        board->mode = INIT;
        return 0;
        /*dont have to clean board still in INIT mode*/
    }
    else{
        board->mode=SOLVE;
        return 1;
    }
}  

/*COMMAND 2*/
/* in Edit mode we always mark errors, regardless of the value of the "mark errors", remains value*/
int edit(Board* board, char* path) {
    if(path == NULL){
        create_empty_board(board,3,3); 
    }
    else{
        int succeeded;
        succeeded = read_file_to_board(board,path,0);
        if(succeeded == 0){
            printf("Error: invalid file\n");
            board->mode = INIT;
            return 0;
            /*dont have to clean board still in INIT mode*/
        }
    }
    board->mode = EDIT; 
    return 1;
}

/*COMMAND 3*/
/* is_mark is 1 or 0 */
void mark_errors(Board* board, int is_mark){
    board->mark_errors = is_mark;
} 

/*COMMAND 4*/
void print_board(Board* board){
    int a, b, c, d;
    int row, col, value;
    int separator, i;
    separator = 4*board->num_of_columns*board->num_of_rows + board->num_of_rows + 1;
    for(a = 0; a < board->num_of_columns; a++){ 
        
        for(i=0;i<separator;i++){
            printf("-");
        }
        printf("\n"); 
        
        for(b = 0; b < board->num_of_rows; b++){
            row = b + a*(board->num_of_rows);
            printf("| "); /*space?*/
            for(c = 0; c < board->num_of_rows; c++){
                for(d = 0; d < board->num_of_columns; d++){
                    col = d + c*board->num_of_columns;
                    value = get_value(row,col,board,0);
                    if(board->fixed_board[row][col] != BOARD_NULL_VALUE){
                        printf(" %2d.",value);
                    }
                    else{
                        if(value != BOARD_NULL_VALUE){
                            board->cur_board[row][col]=BOARD_NULL_VALUE; /*not clash with himself*/
                            if(is_legal(row,col,value,board,0) == 0 && (board->mode==EDIT || board->mark_errors == 1)){
                                printf(" %2d*",value);
                            }
                            else{
                                printf(" %2d ",value);
                            }
                            board->cur_board[row][col]=value;
                        }   
                        else
                            printf("    ");
                    } 
                }
                if(c != (board->num_of_rows-1))
                    printf("| "); /*space?*/
            }
            printf("|\n");
        }     
    }

    for(i=0;i<separator;i++){
            printf("-");
        }
    printf("\n");

}

/*COMMAND 5*/
/*TODO: mode edit? is winner? with/without print board?*/
int set_value_user(int x, int y, int value, Board* board){
    int size = board->num_of_columns * board->num_of_rows;
    if(x<0 || x>=size || y<0 || y>=size || value <0 || value>size){
        printf("Error: out of range\n");
        return 0;
    }
    if((board->fixed_board)[x][y] != BOARD_NULL_VALUE && board->mode == SOLVE){
        printf("Error: cell is fixed\n");
        return 0;
    }
    if(value == 0){
        erase_value(x,y,board);
        print_board(board);
        return 1;
    }
    board->cur_board[x][y] = value;
    
    if(board->mode == EDIT){
       board->fixed_board[x][y] = value; 
    }
    board->count_filled++;
    print_board(board);
    if(is_winner(board) == 1){
        printf("Puzzle solved successfully\n");
    }
    return 1;   
}

/*COMMAND 6*/
/* TODO: change to validate with ILP*/ 
void validate_board(Board* board){
    int **cur_board_copy;
    int valid_board = 0;
    int fixed = board->count_filled;
    int size = board->num_of_rows * board->num_of_columns;
    cur_board_copy = create_2d_array(size);
    copy_board_values(cur_board_copy, board->cur_board, size);
    valid_board = back_track(board,1); /*deterministic*/

    copy_board_values(board->cur_board, cur_board_copy, size);
    free_2d_array(cur_board_copy, size);

    board ->count_filled= fixed;
    if(valid_board == 0)/*not vaild*/
        printf("Validation failed: board is unsolvable\n");
    else
        printf("Validation passed: board is solvable\n");
}

/*COMMAND 7*/
/* TODO: guess with LP*/
void guess(float threshold);

/*COMMAND 8*/
/* TODO: generate with ILP*/
void generate();

/*COMMAND 9*/
void undo(Board* board, Moves* moves);

/*COMMAND 10*/
void redo(Board* board, Moves* moves);

/*COMMAND 11*/
int save(Board* board, char* path){
    int succeeded;
    succeeded = write_file_from_board(board,path);
    return succeeded;
}

/*COMMAND 12*/
/* TODO: hint with ILP + check range of x,y*/
void hint(int x, int y, Board* board){
    int value = board->solved_board[x-1][y-1];
    printf("Hint: set cell to %d\n",value);
}

/*COMMAND 13*/
/* TODO: hint with LP*/
void guess_hint();

/*COMMAND 14*/
int number_solutions(Board* board) {
    int number;
    number = stack_based_back_track(board);
    printf("the number of solutions is: %d \n",number);
    return 0;
}

/*COMMAND 15*/
void autofill();

/*COMMAND 16*/
void reset();
/* set BOARD_NULL_VALUE to cur/solved/fixed and count_filled = 0
call generate_puzzle with user new fixed */
void restart(Board* board){
    int fixed, i, j;
    int size = (board->num_of_rows)*(board->num_of_columns);
    int max_fill = size*size-1;
    int count_scan;
    printf("Please enter the number of cells to fill [0-%d]:\n",max_fill);

    count_scan = scanf("%d",&fixed);
    if(feof(stdin)){exit_game(board);}
    if(count_scan == 0){printf("Error: not a number\n");exit_game(board);}
    /*if(count_scan < 0){printf("Error: scanf has failed\n");exit(0);}*/

    while(fixed<0 || fixed>max_fill){ /*assume the user enters a single valid integer*/
        printf("Error: invalid number of cells to fill (should be between 0 and %d)\n",max_fill);
        printf("Please enter the number of cells to fill [0-%d]:\n",max_fill);
        count_scan = scanf("%d",&fixed);
        if(feof(stdin)){exit_game(board);}
        if(count_scan == 0){printf("Error: not a number\n");exit_game(board);}
        /*if(count_scan < 0){printf("Error: scanf has failed\n");exit(0);}*/
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