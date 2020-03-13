
#ifndef SOFTWAREPROJ_gurobi_variable_H
#define SOFTWAREPROJ_gurobi_variable_H

/* holds the linkage between a gurobi index and the data it represents */
typedef struct _gurobi_variable
{
    int row;
    int column;
    int possible_value;
    int index_in_gurobi;

} gurobi_var;


#endif
