#include "parser.h"
#include "sudoku_board_actions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* interpret user input and call actions
return num op or 0 if invalid command
if board filled can restart and exit only */
int parse_command(char* command, Board* board){
    int x,y,z;
    char* token;
    int filled = is_filled(board);

    token = strtok(command," \t\r\n");
    
    if(token == NULL){return 0;}

    if(strcmp(token, "set") == 0 && !filled){

        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        y = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        z = atoi(token);

        set_value_user(y,x,z,board);
        return 1;
    }

    if(strcmp(token, "hint") == 0 && !filled){

        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        y = atoi(token);

        hint(y,x,board);
        return 2;
    }

    if(strcmp(token, "validate") == 0 && !filled){
        validate_board(board);
        return 3;
    }

    if(strcmp(token, "restart") == 0){
        restart(board);
        return 4;
    }

    if(strcmp(token, "exit") == 0){
        free(command);
        exit_game(board);
        return 5;
    }
    
    /*a command that doesn't match any of the commands defined*/
    printf("Error: invalid command\n");
    return 0;
}
