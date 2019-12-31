#include "parser.h"
#include "sudoku_board_actions.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    int seed_num;
    char* command = malloc((sizeof(char)*1024));
    Board* board = malloc((sizeof(Board)));

    if(command==NULL){printf("Error: malloc has failed\n");exit(0);}
    if(board==NULL){printf("Error: malloc has failed\n");exit(0);}

    if (argc  <= 1) {
        return 0;
    }
    seed_num = (argv[1][0] - '0');
    seed(seed_num);

    create_empty_board(board,3,3);
    restart(board);

    if(feof(stdin)){exit_game(board);}
    while(1){
        fgets(command,1024,stdin);
        parse_command(command, board);
        if(feof(stdin)){exit_game(board);}
    }

    return 0;
}