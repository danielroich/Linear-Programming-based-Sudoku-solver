#include "parser.h"
#include "sudoku_board_actions.h"
#include "optional_cell_values.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_error_mode(const char *ava_modes)
{
    printf("Error: command is unavailable in the current mode. available mode: %s.\n", ava_modes);
}

void print_error_not_enough(const char *correct)
{
    printf("Error: not enough parameters. correct command: %s.\n", correct);
}

void print_error_too_many(const char *correct)
{
    printf("Error: too many parameters. correct command: %s.\n", correct);
}

/* interpret user input and call actions
return num op or 0 if invalid command/error */
int parse_command(char *command, Board *board, Curr_move move)
{
    int x, y, z;
    float threshold;
    char *token, *next;
    int succeeded;
    int size = board->num_of_columns * board->num_of_rows;
    int i = 0;

    token = strtok(command, " \t\r\n");
    if (token == NULL)
    {
        return 0;
    }

    /*COMMAND 1*/
    if (strcmp(token, "solve") == 0)
    {
        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("solve filepath");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("solve filepath");
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
        if (next != NULL)
        {
            print_error_too_many("edit or edit filepath");
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
        if (board->mode != SOLVE)
        {
            print_error_mode("solve");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("mark_errors 0 or mark_errors 1");
            return 0;
        }
        x = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("mark_errors 0 or mark_errors 1");
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
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("print_board");
            return 0;
        }
        print_board(board);
        return 4;
    }

    /*COMMAND 5*/
    if (strcmp(token, "set") == 0)
    {
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("set column row value");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("set column row value");
            return 0;
        }
        y = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("set column row value");
            return 0;
        }
        z = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("set column row value");
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

    /*COMMAND 6*/
    if (strcmp(token, "validate") == 0)
    {
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("validate");
            return 0;
        }

        if (is_erroneous_board(board))
        {
            printf("Error: erroneous boards can't be validate.\n");
            return 0;
        }

        validate_board(board);
        return 6;
    }

    /*COMMAND 7*/
    if (strcmp(token, "guess") == 0)
    {
        if (board->mode != SOLVE)
        {
            print_error_mode("solve");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("guess threshold");
            return 0;
        }
        threshold = atof(token);

        next = (strtok(NULL, " \t\r\n"));
        if(next != NULL)
        {
            print_error_too_many("guess threshold");
            return 0;
        }
        
        if (is_erroneous_board(board))
        {
            printf("Error: erroneous boards can't use guess.\n");
            return 0;
        }

        guess(board, threshold); 
    
        /* TODO:
        succeeded =
        if (succeeded == 1)
        {
            clean_nexts(move);
            add_new_move(move, board);
            print_board(board);
            return 7;
        }
        */
       return 0;
    }

    /*COMMAND 8*/
    if (strcmp(token, "generate") == 0)
    {
        if (board->mode != EDIT)
        {
            print_error_mode("edit");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("generate fill keep");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("generate fill keep");
            return 0;
        }
        y = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("generate fill keep");
            return 0;
        }

        do{
            succeeded = generate(board, x, y);
            i++;
        } while(i<1000 && succeeded==0);
        if(succeeded==0){
            printf("Error: in the puzzle generator.\n");
        }
        if (succeeded == 1)
        {
            clean_nexts(move);
            add_new_move(move, board);
            print_board(board);
            return 8;
        }

        return 8;
    }

    /*COMMAND 9*/
    if (strcmp(token, "undo") == 0)
    {
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("undo");
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
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("redo");
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
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("save filepath");
            return 0;
        }

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("save filepath");
            return 0;
        }

        succeeded = save(board, token);
        if (!succeeded)
            return 0;
        return 11;
    }

    /*COMMAND 12*/
    if (strcmp(token, "hint") == 0)
    {
        if (board->mode != SOLVE)
        {
            print_error_mode("solve");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("hint column row");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("hint column row");
            return 0;
        }
        y = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("hint column row");
            return 0;
        }

        if (x < 1 || x > size)
        {
            printf("Error: first parameter out of range. legal range for column: %d - %d.\n", 1, size);
            return 0;
        }
        if (y < 1 || y > size)
        {
            printf("Error: second parameter out of range. legal range for row: %d - %d.\n", 1, size);
            return 0;
        }

        if (is_erroneous_board(board))
        {
            printf("Error: erroneous boards can't use hint.\n");
            return 0;
        }

        if (board->fixed_board[y - 1][x - 1] != BOARD_NULL_VALUE)
        {
            printf("Error: cell (%d,%d) is fixed.\n", y, x);
            return 0;
        }
        if (board->cur_board[y - 1][x - 1] != BOARD_NULL_VALUE)
        {
            printf("Error: cell (%d,%d) already contains a value.\n", y, x);
            return 0;
        }

        hint(y-1, x-1, board);
        return 12;
    }

    /*COMMAND 13*/
    if (strcmp(token, "guess_hint") == 0)
    {
        if (board->mode != SOLVE)
        {
            print_error_mode("solve");
            return 0;
        }

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("guess_hint column row");
            return 0;
        }
        x = atoi(token);

        token = (strtok(NULL, " \t\r\n"));
        if (token == NULL)
        {
            print_error_not_enough("guess_hint column row");
            return 0;
        }
        y = atoi(token);

        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("guess_hint column row");
            return 0;
        }

        if (x < 1 || x > size)
        {
            printf("Error: first parameter out of range. legal range for column: %d - %d.\n", 1, size);
            return 0;
        }
        if (y < 1 || y > size)
        {
            printf("Error: second parameter out of range. legal range for row: %d - %d.\n", 1, size);
            return 0;
        }

        if (is_erroneous_board(board))
        {
            printf("Error: erroneous boards can't use guess_hint.\n");
            return 0;
        }

        if (board->fixed_board[y - 1][x - 1] != BOARD_NULL_VALUE)
        {
            printf("Error: cell (%d,%d) is fixed.\n", y, x);
            return 0;
        }

        if (board->cur_board[y - 1][x - 1] != BOARD_NULL_VALUE)
        {
            printf("Error: cell (%d,%d) already contains a value.\n", y, x);
            return 0;
        }

        guess_hint(board,y-1,x-1);
        return 13;
    }

    /*COMMAND 14*/
    if (strcmp(token, "num_solutions") == 0)
    {
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("num_solutions");
            return 0;
        }
        number_solutions(board);
        return 14;
    }

    /*COMMAND 15*/
    if (strcmp(token, "autofill") == 0)
    {
        if (board->mode != SOLVE)
        {
            print_error_mode("solve");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("autofill");
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
        if (board->mode == INIT)
        {
            print_error_mode("solve or edit");
            return 0;
        }
        next = (strtok(NULL, " \t\r\n"));
        if (next != NULL)
        {
            print_error_too_many("reset");
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
        if (next != NULL)
        {
            print_error_too_many("exit");
            return 0;
        }
        free(command);
        exit_game(board, move);
        return 17;
    }

    /*a command that doesn't match any of the commands defined.*/
    printf("Error: no such command exists.\n");
    return 0;
}
