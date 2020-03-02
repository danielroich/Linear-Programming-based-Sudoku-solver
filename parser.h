/* parse user command and call function from actions accordingly
check if available mode ,not enough/too many/vaild parameters*/

#ifndef EX3_PARSER_H
#define EX3_PARSER_H

#include "sudoku_board.h"
#include "moves.h"

int parse_command(char* command, Board* board, Curr_move move);

#endif
