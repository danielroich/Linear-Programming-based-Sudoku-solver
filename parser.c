#include "parser.h"
#include "sudoku_board_actions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* interpret user input and call actions
return num op or 0 if invalid command
if board filled can restart and exit only */
int parse_command(char* command, Board* board, Moves* moves){
    int x,y,z;
    char* token;
    int filled = is_filled(board);

    token = strtok(command," \t\r\n");
    
    if(token == NULL){return 0;}

    /*COMMAND 1*/ 
    if(strcmp(token, "solve")==0){
        return 1;
    }
    
    /*COMMAND 2*/ 
    if(strcmp(token, "edit")==0){
        return 2;
    }
    
    /*COMMAND 3*/ 
    if(strcmp(token, "mark_errors")==0 && board->mode == SOLVE){
        return 3;
    }

    /*COMMAND 4*/ 
    if(strcmp(token, "print_board")==0 && board->mode != INIT){
        return 4;
    }

    /*COMMAND 5*/
    if(strcmp(token, "set") == 0 && board->mode != INIT && !filled){

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
        return 5;
    }

    /*COMMAND 6*/
    if(strcmp(token, "validate") == 0 && board->mode != INIT && !filled){
        validate_board(board);
        return 6;
    }

    /*COMMAND 7*/
    if(strcmp(token,"guess")==0 && board->mode == SOLVE){
        return 7;
    }

    /*COMMAND 8*/
    if(strcmp(token,"generate")==0 && board->mode == EDIT){
        return 8;
    }

    /*COMMAND 9*/
    if(strcmp(token,"undo")==0 && board->mode != INIT){
        return 9;
    }

    /*COMMAND 10*/
    if(strcmp(token,"redo")==0 && board->mode != INIT){
        return 10;
    }

    /*COMMAND 11*/
    if(strcmp(token,"save")==0 && board->mode != INIT){
        return 11;
    }

    /*COMMAND 12*/
    if(strcmp(token, "hint") == 0 && board->mode == SOLVE && !filled){

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
        return 12;
    }

    /*COMMAND 13*/
    if(strcmp(token,"guess_hint")==0 && board->mode == SOLVE){
        return 13;
    }

    /*COMMAND 14*/
    if(strcmp(token, "num_solutions") == 0 && board->mode != INIT){
        int num = number_of_solutions(board);
        printf("the number of solutions is: %d \n",num);
        return 14;
    }

    /*COMMAND 15*/
    if(strcmp(token,"autofill")==0 && board->mode == SOLVE){
        return 15;
    }

    /*COMMAND 16*/
    if(strcmp(token,"reset") ==0 && board->mode != INIT){
        return 16;
    }
    if(strcmp(token, "restart") == 0){
        restart(board);
        return 16;
    }

    /*COMMAND 17*/
    if(strcmp(token, "exit") == 0){
        free(command);
        exit_game(board);
        return 17;
    }

    /*a command that doesn't match any of the commands defined 
    or not in right Mode*/
    printf("Error: invalid command\n");
    return 0;
}
