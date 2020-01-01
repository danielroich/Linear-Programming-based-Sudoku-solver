#include "parser.h"
#include "sudoku_board_actions.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_SEED 5

int main(int argc, char *argv[]) {

    int seed_num;
    char* command = malloc((sizeof(char)*1024));
    Board* board = malloc((sizeof(Board)));

    if(command==NULL){printf("Error: malloc has failed\n");exit(0);}
    if(board==NULL){printf("Error: malloc has failed\n");exit(0);}

    if (argc  <= 1) {
        seed_num = DEFAULT_SEED;
    }
    else {

        seed_num = atoi(argv[1]);
    }

    seed(seed_num);
    create_empty_board(board,3,3);
    restart(board);

    while(!feof(stdin)){
        fgets(command,1024,stdin);
        parse_command(command, board);
    }
    exit_game(board);

    return 0;
}
