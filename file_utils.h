/* read and write from and to files */

#ifndef SOFTWAREPROJ_FILE_UTILS_H
#define SOFTWAREPROJ_FILE_UTILS_H

#include "sudoku_board.h"

int read_file_to_board (Board* board, const char* path, int check_errors);
int write_file_from_board (Board* board, const char* path);

#endif
