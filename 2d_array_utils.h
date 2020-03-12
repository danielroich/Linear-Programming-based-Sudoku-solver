#ifndef SOFTWAREPROJ_2D_ARRAY_UTILS_H
#define SOFTWAREPROJ_2D_ARRAY_UTILS_H

#include "optional_cell_values.h"

void copy_board_values(int** to, int** from, int size);

void free_2d_array(int **array, int size);

int** create_2d_array(int size);

OptionalCellValues ** create_2d_possible_values_array(int size);

void free_possible_values_2d_array(OptionalCellValues **array, int size);

#endif
