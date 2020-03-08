
#ifndef SOFTWAREPROJ_optional_cell_values_H
#define SOFTWAREPROJ_optional_cell_values_H

#include "possible_value.h"

typedef struct _optional_cell_values_H {
    int row;
    int column;
    PossibleValue* possible_values;

} OptionalCellValues;

void free_cell_values(OptionalCellValues* cell_values);

#endif