#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void create_solved_board(Board *board){
    int i,j;
    int size;
    int sol[9][9];
    int fix [9][9];

    board->num_of_columns = 3;
    board->num_of_rows = 3;
    board->count_filled=72;

    size = board->num_of_columns*board->num_of_rows;
    board->cur_board = (int **)malloc(size * sizeof(int*));
    board->solved_board = (int **)malloc(size * sizeof(int*));
    board->fixed_board = (int **)malloc(size * sizeof(int*));
    for (i=0; i<size; i++){
        board->cur_board[i] = (int *)calloc(size ,sizeof(int));
        board->solved_board[i] = (int *)calloc(size ,sizeof(int));
        board->fixed_board[i] = (int *)calloc(size ,sizeof(int));
    }

    sol = {
    {9,6,8,7,3,1,5,4,2},
    {4,1,2,6,8,5,7,3,9},
    {5,3,7,9,2,4,1,8,6},
    {2,8,9,3,5,7,4,6,1},
    {1,7,4,8,6,9,3,2,5},
    {6,5,3,4,1,2,9,7,8},
    {7,4,5,2,9,6,8,1,3},
    {3,9,6,1,4,8,2,5,7},
    {8,2,1,5,7,3,6,9,4}
    };
    
    fix = {
    {9,6,8,7,3,1,BOARD_NULL_VALUE,4,2},
    {4,BOARD_NULL_VALUE,2,6,8,5,7,BOARD_NULL_VALUE,9},
    {5,3,BOARD_NULL_VALUE,9,2,4,1,8,BOARD_NULL_VALUE},
    {2,8,9,3,5,7,4,6,1},
    {1,BOARD_NULL_VALUE,4,8,6,9,3,2,5},
    {6,BOARD_NULL_VALUE,BOARD_NULL_VALUE,4,1,2,9,7,8},
    {7,4,5,2,9,6,8,1,3},
    {3,9,BOARD_NULL_VALUE,1,4,8,2,5,7},
    {8,2,1,5,7,3,6,9,4}
    };
    
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            board->fixed_board[i][j]=fix[i][j];
            board->cur_board[i][j]=fix[i][j];
            board->solved_board[i][j]=sol[i][j];
        }    
    }
}

void test_set_user(Board *board){
    set_value_user(1,3,8,board); //in fixed
    set_value_user(1,3,0,board); //in fixed
    set_value_user(2,2,7,board); //in row
    set_value_user(3,3,6,board); //in square
    set_value_user(6,2,3,board); //in col
    
    set_value_user(2,2,1,board); //right set
    printf("%d\n",board->count_filled);

    set_value_user(2,2,0,board); //erase set
    printf("%d\n",board->count_filled);

    hint(3,3,board);
}

void create_80_board(Board *board){
    int i;    
    board->num_of_columns = 3;
    board->num_of_rows = 3;
    board->count_filled=80;
    int size = board->num_of_columns*board->num_of_rows;

    board->cur_board = (int **)malloc(size * sizeof(int*));
    board->solved_board = (int **)malloc(size * sizeof(int*));
    board->fixed_board = (int **)malloc(size * sizeof(int*));
    for (i=0; i<size; i++){
        board->cur_board[i] = (int *)calloc(size ,sizeof(int));
        board->solved_board[i] = (int *)calloc(size ,sizeof(int));
        board->fixed_board[i] = (int *)calloc(size ,sizeof(int));
    }

    int sol[9][9] = {
    {9,6,8,7,3,1,5,4,2},
    {4,1,2,6,8,5,7,3,9},
    {5,3,7,9,2,4,1,8,6},
    {2,8,9,3,5,7,4,6,1},
    {1,7,4,8,6,9,3,2,5},
    {6,5,3,4,1,2,9,7,8},
    {7,4,5,2,9,6,8,1,3},
    {3,9,6,1,4,8,2,5,7},
    {8,2,1,5,7,3,6,9,4}
    };
    
    int fix [9][9] = {
    {9,6,8,7,3,1,5,4,2},
    {4,1,2,6,8,5,7,3,9},
    {5,3,7,9,2,4,1,8,6},
    {2,8,9,3,5,7,4,6,1},
    {1,7,4,8,6,9,3,2,5},
    {6,5,3,4,1,2,9,7,8},
    {7,4,5,2,9,6,8,1,3},
    {3,9,6,1,4,8,2,5,7},
    {8,2,1,5,7,3,6,9,BOARD_NULL_VALUE}
    };
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board->fixed_board[i][j]=fix[i][j];
            board->cur_board[i][j]=fix[i][j];
            board->solved_board[i][j]=sol[i][j];
        }    
    }
}

int main() {

    Board *board = malloc(sizeof(Board));
    create_solved_board(board);
    test_set_user(board);
    
    //create_80_board(board);
    //set_value_user(9,9,4,board); //winner test
    //char* com= "set 9 9 4";
    //parse_command(com,board);

}