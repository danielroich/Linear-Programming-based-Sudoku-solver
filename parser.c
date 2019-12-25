#include "parser.h"
#include <string.h>

int parse_command(char* command, Board* board){
    int x,y,z;
    char* token = strtok(command," \t\r\n");
    int filled = is_filled(board);

    if(strcmp(token, "set") == 0 && !filled){
        x = strtok(NULL, command);
        y = strtok(NULL, command);
        z = strtok(NULL, command);
        set_value_user(x,y,z,board);
        return 1;
    }

    if(strcmp(token, "hint") == 0 && !filled){
        x = strtok(NULL, command);
        y = strtok(NULL, command);
        hint(x,y,z,board);
        return 2;
    }

    if(strcmp(token, "validate" ) == 0 && !filled){
        validate_board(board);
        return 3;
    }

    if(strcmp(token, "restart") == 0){
        restart(board);
        return 4;
    }

    if(strcmp(token, "exit") == 0){
        exit_game(board);
        return 5;
    }

    /*a command that doesn't match any of the commands defined*/
    printf("Error: invalid command\n");
    return 0;
}

