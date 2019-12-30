#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
/* interpret user input and call actions
return num op or 0 if invalid command
if board filled can restart and exit only */
int parse_command(char* command, Board* board){
    char* command_parse=malloc(1024*sizeof(char));
    int x,y,z;
    char* token; 
    int filled = is_filled(board);
    strcpy(command_parse,command);

    token = strtok(command_parse," \t\r\n");
    
    if(token == NULL){free(token);return 0;}

    if(strcmp(token, "set") == 0 && !filled){
        token = (strtok(NULL, " \t\r\n"));
        x = atoi(token);
        token = (strtok(NULL, " \t\r\n"));
        y = atoi(token);
        token = (strtok(NULL, " \t\r\n"));
        z = atoi(token);
        set_value_user(x,y,z,board);
        free(token);
        return 1;
    }

    if(strcmp(token, "hint") == 0 && !filled){
        token = (strtok(NULL, " \t\r\n"));
        x = atoi(token);
        token = (strtok(NULL, " \t\r\n"));
        y = atoi(token);
        hint(x,y,board);
        free(token);
        return 2;
    }

    if(strcmp(token, "validate") == 0 && !filled){
        validate_board(board);
        free(token);
        return 3;
    }

    if(strcmp(token, "restart") == 0){
        restart(board);
        free(token);
        return 4;
    }

    if(strcmp(token, "exit") == 0){
        exit_game(board);
        free(token);
        return 5;
    }
    
    free(token);
    /*a command that doesn't match any of the commands defined*/
    printf("Error: invalid command\n");
    return 0;
}