#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    char* command = malloc((sizeof(char)*1024)); 
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board,3,3);
    restart(board);
    print_board(board);
    if(feof(stdin)){exit_game(board);}
    while(1==1){
        fgets(command,1024,stdin);
        parse_command(command, board);
        if(feof(stdin)){exit_game(board);}
    }
    return 0;
}