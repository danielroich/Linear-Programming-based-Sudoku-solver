
#ifndef SOFTWAREPROJ_optional_cell_values_H
#define SOFTWAREPROJ_optional_cell_values_H

/* the propabilities array is the size of the square size, and it hold probs for each value, of course
if the value is not possible it's prob will be 0*/
typedef struct _optional_cell_values_H {
    int row;
    int column;
    float* propabilities;
    int chosen_value;

} OptionalCellValues;


#endif