#include <stdio.h>
#include <stdlib.h>
#include "sudoku_board_actions.h"
#include "backtracking_core_logic.h"
#include "puzzle_generator.h"
#include "2d_array_utils.h"
#include "file_utils.h"
#include "stack_backtrack_logic.h"
#include "puzzle_generator.h"
#include "LP.h"

int is_winner(Board* board){
    if(is_filled(board) && is_erroneous_board(board)==0)
        return 1;
    return 0;
}

/*COMMAND 17*/
/* free memo and exit*/
void exit_game(Board* board, Curr_move move){
    printf("Exiting...\n");
    free_board(board);
    clean_list(move);
    exit(0);
}

/*COMMAND 1*/ 
int solve(Board* board, char* path){
    int succeeded;
    succeeded = read_file_to_board(board,path,1);
    if(succeeded == 0){
        printf("Error: invalid file\n");
        return 0;
        /*board->mode = INIT; or stay ? dont have to clean board still in INIT mode*/
    }
    else{
        board->mode=SOLVE;
        return 1;
    }
}  

/*COMMAND 2*/
int edit(Board* board, char* path) {
    if(path == NULL){
        create_empty_board(board,3,3); 
    }
    else{
        int succeeded;
        succeeded = read_file_to_board(board,path,0);
        if(succeeded == 0){
            printf("Error: invalid file\n");
            return 0;
        /*board->mode = INIT; or stay ? dont have to clean board still in INIT mode*/
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
    /*printf("count_filled %d \n",board->count_filled); del!*/ 
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
                    if(board->fixed_board[row][col] != BOARD_NULL_VALUE && board->mode==SOLVE){
                        printf(" %2d.",value);
                    }
                    else{
                        if(value != BOARD_NULL_VALUE){
                            if(is_erroneous_cell(board,row,col) && (board->mode==EDIT || board->mark_errors == 1)){
                                printf(" %2d*",value);
                            }
                            else{
                                printf(" %2d ",value);
                            }
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

    if(board->mode == SOLVE && is_winner(board)){
        printf("Puzzle solved successfully\n");
        board->mode = INIT;
    }

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
        return 1;
    }
    set_value_without_check(x,y,value,board);
    return 1;   
}

/*COMMAND 6*/
/* TODO: validate with ILP*/ 
void validate_board(Board* board){
    int **cur_board_copy;
    int valid_board = 0;
    int fixed = board->count_filled;
    int size = board->num_of_rows * board->num_of_columns;
    cur_board_copy = create_2d_array(size);
    copy_board_values(cur_board_copy, board->cur_board, size);
    
    valid_board = validate_ILP(board);
    copy_board_values(board->cur_board, cur_board_copy, size);
    free_2d_array(cur_board_copy, size);

    board ->count_filled= fixed;
    if(valid_board != 1)/*not vaild*/
        printf("Validation failed: board is unsolvable\n");
    else
        printf("Validation passed: board is solvable\n");
}

/*COMMAND 7*/
void guess(Board* board, int row, int coulmn, float threshold) {
    int value = guess_LP(board,row,coulmn, threshold);
    printf("%d, %f\n",value,threshold);
}

/*COMMAND 8*/
/* TODO: generate with ILP*/
void generate();

/*COMMAND 9*/
int undo(Board* board, Curr_move move){
    if(!curr_to_prev(move)){
        return 0;
    }
    print_diff(board,(*move)->Board_state);
    copy_board((*move)->Board_state,board);
    return 1;
}

/*COMMAND 10*/
int redo(Board* board, Curr_move move){
    if(!curr_to_next(move)){
        return 0;
    }
    print_diff(board,(*move)->Board_state);
    copy_board((*move)->Board_state,board);
    return 1;
}

/*COMMAND 11*/
int save(Board* board, char* path){
    int succeeded;
    if(board->mode == EDIT && is_erroneous_board(board)){
        printf("Error: in EDIT mode erroneous boards can't be saved \n");
        return 0;
    }
    /*if(board->mode == EDIT && !validate_board(board)){
        printf("Error: in EDIT mode boards without a solution can't be saved\n");
        return 0;
    } TODO: validate to int-return-value */
    succeeded = write_file_from_board(board,path);
    return succeeded;
}

/*COMMAND 12*/
/* TODO: hint with ILP + check range of x,y! */
void hint(int x, int y, Board* board){
    int value = hint_ILP(board,x,y);
    /*int value = board->solved_board[x-1][y-1]; */
    printf("Hint: set cell to %d\n",value);
}

/*COMMAND 13*/
/* TODO: hint with LP*/
void guess_hint();

/*COMMAND 14*/
int number_solutions(Board* board) {
    int number;
    if(is_erroneous_board(board)){
        printf("Error: erroneous board\n");
        return 0;
    }
    number = stack_based_back_track(board);
    printf("the number of solutions is: %d \n",number);
    return 1;
}

/*COMMAND 15*/
int autofill(Board* board){
    int i, j, value;
    int size = (board->num_of_rows)*(board->num_of_columns);
    int ** autofill_values = create_2d_array(size);
    if(is_erroneous_board(board)){
        printf("Error: erroneous boards can't be autofill \n");
        return 0;
    }   
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            if(board->cur_board[i][j]==BOARD_NULL_VALUE){
                value = single_possible_value(i,j,board);
                autofill_values[i][j]=value;
            }
        }
    }
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            if(autofill_values[i][j]!=0){
                set_value_without_check(i,j,autofill_values[i][j],board);
            }
        }
    }
    free_2d_array(autofill_values,size);
    return 1;
}

/*COMMAND 16*/
void reset(Curr_move move, Board* board){
    /*first move is load in EDIT/SOLVE, therefore moves!=NULL*/
    if((*move)->prev){
        back_to_first_move(move);
        copy_board((*move)->Board_state,board);
    }
}

void seed(int seed) {
    srand(seed);
}