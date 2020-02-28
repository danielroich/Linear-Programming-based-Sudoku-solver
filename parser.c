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
        add_new_move(move, board);
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
    if (strcmp(token, "set") == 0 && board->mode != INIT)
    {

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: invalid command\n");
            return 0;
        }
        x = atoi(token);

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
        z = atoi(token);

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
    if (strcmp(token, "validate") == 0 && board->mode != INIT)
    {
        // validate_board(board);
        return 6;
    }

    /*COMMAND 7 TODO*/
    if (strcmp(token, "guess") == 0 && board->mode == SOLVE)
    {
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
    if (strcmp(token, "generate") == 0 && board->mode == EDIT)
    {
        print_board(board); /*if success*/
        return 8;
    }

    /*COMMAND 9*/
    if (strcmp(token, "undo") == 0 && board->mode != INIT)
    {
        succeeded = undo(board, move);
        if (!succeeded)
        {
            printf("Error: There are no moves to undo\n");
            return 0;
        }
        print_board(board);
        return 9;
    }

    /*COMMAND 10*/
    if (strcmp(token, "redo") == 0 && board->mode != INIT)
    {
        succeeded = redo(board, move);
        if (!succeeded)
        {
            printf("Error: There are no moves to redo\n");
            return 0;
        }
        print_board(board);
        return 10;
    }

    /*COMMAND 11*/
    if (strcmp(token, "save") == 0 && board->mode != INIT)
    {
        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: invalid command\n");
            return 0;
        }
        succeeded = save(board, token);
        if (!succeeded)
            return 0;
        return 11;
    }

    /*COMMAND 12 TODO*/
    if (strcmp(token, "hint") == 0 && board->mode == SOLVE)
    {

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: invalid command\n");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            printf("Error: invalid command\n");
            return 0;
        }
        y = atoi(token);
        
        /* TODO: check range of x,y! */

        //hint(y, x, board);
        return 12;
    }

    /*COMMAND 13 TODO*/
    if (strcmp(token, "guess_hint") == 0 && board->mode == SOLVE)
    {
        return 13;
    }

    /*COMMAND 14*/
    if (strcmp(token, "num_solutions") == 0 && board->mode != INIT)
    {
        number_solutions(board);
        return 14;
    }

    /*COMMAND 15*/
    if (strcmp(token, "autofill") == 0 && board->mode == SOLVE)
    {
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
    if (strcmp(token, "reset") == 0 && board->mode != INIT)
    {
        reset(move, board);
        print_board(board);
        return 16;
    }

    /*COMMAND 17*/
    if (strcmp(token, "exit") == 0)
    {
        free(command);
        exit_game(board, move);
        return 17;
    }

    /*a command that doesn't match any of the commands defined.*/
    printf("Error: invalid command\n");
    return 0;
}
