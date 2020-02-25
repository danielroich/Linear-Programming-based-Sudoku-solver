#include "parser.h"
#include "sudoku_board_actions.h"
#include "moves_list.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_SEED 5

int main(int argc, char *argv[]) {

    int seed_num;
    char* command = (char*) malloc((sizeof(char)*1024));
    Board* board = (Board*) malloc((sizeof(Board)));
    Moves* moves = {0};

    if(command==NULL){
        printf("Error: malloc has failed\n");
        free(board);
        free(command);
        exit(0);
    }
    if(board==NULL) {
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
    create_empty_board(board,2,4);
    restart(board);

    while(fgets(command,1024,stdin) && !feof(stdin)){
        parse_command(command, board, moves);
    }

    free(command);
    exit_game(board);
    return 0;
}
