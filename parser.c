#include "parser.h"
#include "sudoku_board_actions.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* interpret user input and call actions
return num op or 0 if invalid command/error */
int parse_command(char *command, Board *board, Curr_move move)
{
    int x, y, z;
    char *token, *next;
    int succeeded;
    int size = board->num_of_columns * board->num_of_rows; 

    token = strtok(command, " \t\r\n");
    if (token == NULL){
        return 0;
    }

    /*COMMAND 1*/
    if (strcmp(token, "solve") == 0)
    {
        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: solve filepath.\n");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: solve filepath.\n");
            return 0;
        }

        succeeded = solve(board, token);
        if (succeeded)
        {
            clean_list(move);
            add_new_move(move, board);
            print_board(board);
            return 1;
        }
        return 0;
    }

    /*COMMAND 2*/
    if (strcmp(token, "edit") == 0)
    {
        token = (strtok(NULL, " \t\r\n")); /*ok if NULL, edit create 9x9 empty*/
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: edit or edit filepath.\n");
            return 0;
        }

        succeeded = edit(board, token);
        if (succeeded)
        {
            clean_list(move);
            add_new_move(move, board);
            print_board(board);
            return 2;
        }
        return 0;
    }

    /*COMMAND 3*/
    if (strcmp(token, "mark_errors") == 0)
    {
        if(board->mode != SOLVE){
            printf("Error: command is unavailable in the current mode. available mode: solve.\n");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: mark_errors 0 or mark_errors 1.\n");
            return 0;
        }
        x = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: mark_errors 0 or mark_errors 1.\n");
            return 0;
        }

        if (x != 0 && x != 1)
        {
            printf("Error: incorrect parameter. correct command: mark_errors 0 or mark_errors 1.\n");
            return 0;
        }

        mark_errors(board, x);
        return 3;
    }

    /*COMMAND 4*/
    if (strcmp(token, "print_board") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: print_board.\n");
            return 0;
        }
        print_board(board);
        return 4;
    }

    /*COMMAND 5*/
    if (strcmp(token, "set") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: set column row value.\n");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: set column row value.\n");
            return 0;
        }
        y = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: set column row value.\n");
            return 0;
        }
        z = atoi(token);
        
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: set column row value.\n");
            return 0;
        }

        succeeded = set_value_user(y - 1, x - 1, z, board);
        if (succeeded == 1)
        {
            clean_nexts(move);
            add_new_move(move, board);
            print_board(board);
            return 5;
        }
        return 0;
    }

    /*COMMAND 6 TODO*/
    if (strcmp(token, "validate") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: validate.\n");
            return 0;
        }

        if(is_erroneous_board(board)){
            printf("Error: erroneous boards can't be validate.\n");
            return 0;
        }
        /*TODO: is_erroneous_board in validate_board ?
        validate_board(board);*/
        return 6;
    }

    /*COMMAND 7 TODO*/
    if (strcmp(token, "guess") == 0)
    {
        if(board->mode != SOLVE){
            printf("Error: command is unavailable in the current mode. available mode: solve.\n");
            return 0;
        }

        /*TODO: only threshold as input!
        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: guess threshold.\n");
            return 0;
        }
        x = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: guess threshold.\n");
            return 0;
        }
        */
        if(is_erroneous_board(board)){
            printf("Error: erroneous boards can't use guess.\n");
            return 0;
        }


        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: invalid command\n");
            return 0;
        }
        y = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: invalid command\n");
            return 0;
        }
        x = atoi(token);

        printf("guess for %d,%d\n", x, y);
        //guess(board, x, y, 0);
        return 7;
    }

    /*COMMAND 8 TODO*/
    if (strcmp(token, "generate") == 0 )
    {
        if(board->mode != EDIT){
            printf("Error: command is unavailable in the current mode. available mode: edit.\n");
            return 0;
        }

        print_board(board); /*if success*/
        return 8;
    }

    /*COMMAND 9*/
    if (strcmp(token, "undo") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: undo.\n");
            return 0;
        }

        succeeded = undo(board, move);
        if (!succeeded)
        {
            printf("Error: there are no moves to undo.\n");
            return 0;
        }
        print_board(board);
        return 9;
    }

    /*COMMAND 10*/
    if (strcmp(token, "redo") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: redo.\n");
            return 0;
        }

        succeeded = redo(board, move);
        if (!succeeded)
        {
            printf("Error: there are no moves to redo.\n");
            return 0;
        }
        print_board(board);
        return 10;
    }

    /*COMMAND 11*/
    if (strcmp(token, "save") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: save filepath.\n");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: save filepath.\n");
            return 0;
        }

        succeeded = save(board, token);
        if (!succeeded)
            return 0;
        return 11;
    }

    /*COMMAND 12 TODO*/
    if (strcmp(token, "hint") == 0)
    {
        if(board->mode != SOLVE){
            printf("Error: command is unavailable in the current mode. available mode: solve.\n");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: hint column row.\n");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: hint column row.\n");
            return 0;
        }
        y = atoi(token);
        
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: hint column row.\n");
            return 0;
        }

        if(x<1 || x>size){
            printf("Error: first parameter out of range. legal range for column: %d - %d .\n",1,size);
            return 0;
        }
        if(y<1 || y>size) {
            printf("Error: second parameter out of range. legal range for row: %d - %d .\n",1,size);
            return 0;
        }

        if(board->fixed_board[y-1][x-1]!=BOARD_NULL_VALUE){
            printf("Error: cell (%d,%d) is fixed.\n",y,x);
            return 0;
        }
        if(board->cur_board[y-1][x-1]!=BOARD_NULL_VALUE){
            printf("Error: cell (%d,%d) already contains a value.\n",y,x);
            return 0;
        }

        //hint(y, x, board);
        return 12;
    }

    /*COMMAND 13 TODO*/
    if (strcmp(token, "guess_hint") == 0)
    {
        if(board->mode != SOLVE){
            printf("Error: command is unavailable in the current mode. available mode: solve.\n");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: guess_hint column row.\n");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: not enough parameters. correct command: guess_hint column row.\n");
            return 0;
        }
        y = atoi(token);
        
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: guess_hint column row.\n");
            return 0;
        }

        if(x<1 || x>size){
            printf("Error: first parameter out of range. legal range for column: %d - %d.\n",1,size);
            return 0;
        }
        if(y<1 || y>size) {
            printf("Error: second parameter out of range. legal range for row: %d - %d.\n",1,size);
            return 0;
        }

        if(is_erroneous_board(board)){
            printf("Error: erroneous boards can't use guess_hint.\n");
            return 0;
        }

        if(board->fixed_board[y-1][x-1]!=BOARD_NULL_VALUE){
            printf("Error: cell (%d,%d) is fixed.\n",y,x);
            return 0;
        }

        if(board->cur_board[y-1][x-1]!=BOARD_NULL_VALUE){
            printf("Error: cell (%d,%d) already contains a value.\n",y,x);
            return 0;
        }
    
        /* TODO: call func, x col, y row (1-size). is_erroneous_board inside?*/

        return 13;
    }

    /*COMMAND 14*/
    if (strcmp(token, "num_solutions") == 0)
    {
         if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: num_solutions.\n");
            return 0;
        }
        number_solutions(board);
        return 14;
    }

    /*COMMAND 15*/
    if (strcmp(token, "autofill") == 0)
    {
        if(board->mode != SOLVE){
            printf("Error: command is unavailable in the current mode. available mode: solve.\n");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: autofill.\n");
            return 0;
        }
        succeeded = autofill(board);
        if (succeeded)
        {
            clean_nexts(move);
            add_new_move(move, board);
            print_board(board);
            return 15;
        }
        return 0;
    }

    /*COMMAND 16*/
    if (strcmp(token, "reset") == 0)
    {
        if(board->mode == INIT){
            printf("Error: command is unavailable in the current mode. available modes: solve or edit.\n");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: reset.\n");
            return 0;
        }
        reset(move, board);
        print_board(board);
        return 16;
    }

    /*COMMAND 17*/
    if (strcmp(token, "exit") == 0)
    {
        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            printf("Error: too many parameters. correct command: exit.\n");
            return 0;
        }
        free(command);
        exit_game(board, move);
        return 17;
    }

    /*a command that doesn't match any of the commands defined.*/
    printf("Error: invalid command.\n");
    return 0;
}
