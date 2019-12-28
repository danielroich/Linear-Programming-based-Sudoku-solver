
#include "2d_array_utils.h"
#include "stdlib.h"

void copy_board_values(int** to, int** from, int size) {
    int i;
    int j;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            to[i][j] = from[i][j];
        }
    }
}

void free_2d_array(int **array, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        free(array[i]);
    }

    free(array);
}
