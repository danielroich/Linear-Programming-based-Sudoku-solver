#ifndef SOFTWAREPROJ_FILES_UTILS_H
#define SOFTWAREPROJ_FILES_UTILS_H

#include "sudoku_board.h"

int read_file_to_board (Board* board, char* path);
int write_file_from_board (Board* board, char* path);

#endif
