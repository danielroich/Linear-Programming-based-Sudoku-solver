#include "parser.h"
#include "sudoku_board_actions.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_SEED 5

int main(int argc, char *argv[]) {

    int seed_num;
    char* command = (char*) malloc((sizeof(char)*1024));
    Board* board = (Board*) malloc((sizeof(Board)));
    Curr_move move = (Move**)malloc(sizeof(Move*));

    if(command==NULL || board==NULL || move==NULL){
        printf("Error: malloc has failed\n");
        free(board);
        free(command);
        exit(0);
    }

    if (argc  <= 1) {
        seed_num = DEFAULT_SEED;
    }
    else {

        seed_num = atoi(argv[1]);
    }
    seed(seed_num);

    printf("Welcome to sudoku! please load board to start.\n");
    *move = NULL; /*TODO?*/

    while(fgets(command,1024,stdin) && !feof(stdin)){
        parse_command(command, board, move);
    }

    free(command);
    exit_game(board,move);
    return 0;
}