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
    int succeeded;
    int filled = is_winner(board); /*TODO*/

    token = strtok(command," \t\r\n");
    if(token == NULL){return 0;}

    /*COMMAND 1*/ 
    if(strcmp(token, "solve")==0){
        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        succeeded = solve(board,token);
        if(succeeded){
            clean_list(moves);
            add_new_move(moves,board);
            return 1;
        }
        return 0;
    }
    
    /*COMMAND 2*/ 
    if(strcmp(token, "edit")==0){
        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            edit(board,NULL);
        }
        succeeded = edit(board,token);
        if(succeeded){
            clean_list(moves);
            add_new_move(moves,board);
            return 2;
        }
        return 0;
    }
    
    /*COMMAND 3*/ 
    if(strcmp(token, "mark_errors")==0 && board->mode == SOLVE){
        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;}
        x = atoi(token);
        if(x!=0 && x!=1){
            printf("Error: invalid command\n");
             return 0;       
        }
        mark_errors(board,x);
        add_new_move(moves,board);
        return 3;
    }

    /*COMMAND 4*/ 
    if(strcmp(token, "print_board")==0 && board->mode != INIT){
        print_board(board);
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

        succeeded = set_value_user(y-1,x-1,z,board);
        if(succeeded == 1){
            add_new_move(moves,board);
        }
        return 5;
    }

    /*COMMAND 6 TODO*/
    if(strcmp(token, "validate") == 0){
        /*  && board->mode != INIT && !filled */
        validate_board(board);
        return 6;
    }

    /*COMMAND 7 TODO*/
    if(strcmp(token,"guess")==0 && board->mode == SOLVE){
        return 7;
    }

    /*COMMAND 8 TODO*/
    if(strcmp(token,"generate")==0 && board->mode == EDIT){
        return 8;
    }

    /*COMMAND 9*/
    if(strcmp(token,"undo")==0 && board->mode != INIT){
        succeeded = undo(board,moves);
        if (!succeeded){
            printf("Error: There are no moves to undo\n");
            return 0;
        }
        return 9;
    }

    /*COMMAND 10*/
    if(strcmp(token,"redo")==0 && board->mode != INIT){
        succeeded = redo(board,moves);
        if (!succeeded){
            printf("Error: There are no moves to redo\n");
            return 0;
        }
        return 10;
    }

    /*COMMAND 11*/
    if(strcmp(token,"save")==0 && board->mode != INIT){
        token = (strtok(NULL, " \t\r\n"));
        if(token == NULL){
            printf("Error: invalid command\n");
            return 0;
        }
        succeeded = save(board,token);
        if(!succeeded)
            return 0;
        return 11;
    }

    /*COMMAND 12 TODO*/
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

    /*COMMAND 13 TODO*/
    if(strcmp(token,"guess_hint")==0 && board->mode == SOLVE){
        return 13;
    }

    /*COMMAND 14*/
    if(strcmp(token, "num_solutions") == 0 && board->mode != INIT){
        number_solutions(board);
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
