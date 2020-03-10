#include "stdio.h"
#include "stdlib.h"
#include "optional_cell_values.h"

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

int**  create_2d_array(int size) {
    int i;
    int ** array;
    array = (int **)malloc(size * sizeof(int*));

    if (array == NULL) {
        printf("Error: create_2d_array has failed\n");
        exit(0);
    }

    for (i=0; i<size; i++) {
        array[i] = (int *) calloc(size, sizeof(int));

        if(array[i] == NULL) {
            printf("Error: create_2d_array has failed\n");
            exit(0);
        }
    }

    return array;
}

OptionalCellValues ** create_2d_possible_values_array(int size) {
    int i;
    OptionalCellValues ** array;
    array = (OptionalCellValues **)calloc(size , sizeof(OptionalCellValues*));

    if (array == NULL) {
        printf("Error: create_2d_array has failed\n");
        exit(0);
    }

    for (i=0; i<size; i++) {
        array[i] = (OptionalCellValues *) calloc(size, sizeof(OptionalCellValues));

        if(array[i] == NULL) {
            printf("Error: create_2d_array has failed\n");
            exit(0);
        }
    }

    return array;
}
