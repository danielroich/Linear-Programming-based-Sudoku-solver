#include "parser.h"
#include "sudoku_board_actions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_SEED 5

int main(int argc, char *argv[]) {

    int seed_num;
    char* command = (char*) malloc((sizeof(char)*256));
    if(command==NULL){
        printf("Error: malloc has failed.\n");
        exit(0);
    }

    Board* board = (Board*) malloc((sizeof(Board)));
    if(board==NULL){
        free(command);
        printf("Error: malloc has failed.\n");
        exit(0);
    }

    Curr_move move = (Move**)malloc(sizeof(Move*));
    if(move==NULL){
        free(command);
        free(board);
        printf("Error: malloc has failed.\n");
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
    *move = NULL;
    board->mode=INIT;

    while(fgets(command,256,stdin) && !feof(stdin)){
        if(strlen(command)==255 && command[255]!='\n'){
            printf("Error: too many characters were entered in a single line.\n");
            /*the entire line may be ignored*/
            while(!feof(stdin) && fgetc(stdin)!='\n')
                continue;
        }
        else
            parse_command(command, board, move);
    }

    free(command);
    exit_game(board, move);
    return 0;
}