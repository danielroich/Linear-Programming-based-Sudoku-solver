#include "optional_cell_values.h"
#include <stdlib.h>

void free_cell_values(OptionalCellValues* cell_values) {
    free(cell_values->possible_values);
    free(cell_values);
}

