#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LP.h"
#include "gurobi_c.h"
#include "backtrack_core.h"
#include <time.h>
#include <limits.h>
#include "2d_array_utils.h"
#include <math.h>
#include "gurobi_variable.h"

int get_num_of_parameters(Board *board)
{
    int i;
    int j;
    int counter = 0;
    int possible_values_num;
    int board_size = board->num_of_columns * board->num_of_rows;
    int *possible_values = (int *)calloc(board_size, sizeof(int));
    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            if (get_value(i, j, board, 0) != BOARD_NULL_VALUE)
                continue;

            possible_values_num = get_possible_values(board, i, j, possible_values);
            counter += possible_values_num;
        }
    }

    return counter;
}

gurobi_var *initilize_gurobi_vars(int num_of_params, Board *board)
{

    int i;
    int j;
    int s;
    int possible_values_num;
    int counter = 0;
    int board_size = board->num_of_columns * board->num_of_rows;
    int *possible_values = (int *)calloc(board_size, sizeof(int));
    gurobi_var *vars = (gurobi_var *)malloc(sizeof(gurobi_var) * num_of_params);

    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            if (get_value(i, j, board, 0) != BOARD_NULL_VALUE)
                continue;

            possible_values_num = get_possible_values(board, i, j, possible_values);
            for (s = 0; s < board_size; s++)
            {
                if (possible_values[s] == 1)
                {
                    vars[counter].column = j;
                    vars[counter].row = i;
                    vars[counter].possible_value = s + 1;
                    vars[counter].index_in_gurobi = counter;
                    ++counter;
                }
            }
        }
    }

    return vars;
}

int get_vars_by_cell(gurobi_var *vars, int row, int column, int bord_size, int num_of_params, int *gurobi_indexes)
{
    int i;
    int k = 0;

    for (i = 0; i < num_of_params; i++)
    {

        if (vars[i].column == column && vars[i].row == row)
        {
            gurobi_indexes[k] = vars[i].index_in_gurobi;
            ++k;
        }
    }

    return k;
}

int get_vars_by_row(gurobi_var *vars, int row, int bord_size, int num_of_params, int *gurobi_indexes, int row_val)
{
    int i;
    int k = 0;
    for (i = 0; i < num_of_params; i++)
    {
        if (vars[i].row == row && vars[i].possible_value == row_val)
        {
            gurobi_indexes[k] = vars[i].index_in_gurobi;
            ++k;
        }
    }

    return k;
}

int get_vars_by_column(gurobi_var *vars, int column, int bord_size, int num_of_params, int *gurobi_indexes, int column_val)
{
    int i;
    int k = 0;
    for (i = 0; i < num_of_params; i++)
    {
        if (vars[i].column == column && vars[i].possible_value == column_val)
        {
            gurobi_indexes[k] = vars[i].index_in_gurobi;
            ++k;
        }
    }

    return k;
}

int get_vars_by_square(gurobi_var *vars, int square_index_to_check, Board *board, int num_of_params, int *gurobi_indexes, int value_in_square, int **square_num_matrix)
{
    int i;
    int j;
    int k = 0;
    int top_left_corner_row;
    int top_left_corner_col;
    int board_size = board->num_of_columns * board->num_of_rows;
    int counter;
    int square_index;

    for (i = 0; i < num_of_params; i++)
    {
        top_left_corner_row = floor(vars[i].row / board->num_of_rows) * board->num_of_rows;
        top_left_corner_col = floor(vars[i].column / board->num_of_columns) * board->num_of_columns;
        square_index = square_num_matrix[(top_left_corner_row / board->num_of_rows)]
                                        [(top_left_corner_col / board->num_of_columns)];

        if (square_index == square_index_to_check && vars[i].possible_value == value_in_square)
        {
            gurobi_indexes[k] = vars[i].index_in_gurobi;
            ++k;
        }
    }

    return k;
}

int add_vectors_to_constraints(GRBmodel *model, int num_of_idexes_for_constraint, int *ind, double *val, GRBenv *env)
{
    int error;
    int k;

    if (num_of_idexes_for_constraint == 0)
        return;

    error = GRBaddconstr(model, num_of_idexes_for_constraint, ind, val, GRB_EQUAL, 1, NULL);
    if (error)
    {
        printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
        return -1;
    }

    /* clean the data */
    for (k = 0; k < num_of_idexes_for_constraint; k++)
    {
        ind[k] = 0;
        val[k] = 0;
    }

    return 1;
}

int add_single_value_per_cell_constraints(Board *board, GRBmodel *model, int *ind, double *val,
                                          GRBenv *env, gurobi_var *vars, int num_of_params)
{
    int i;
    int j;
    int k;
    int board_size = board->num_of_columns * board->num_of_rows;
    int *gurobi_indexes_for_constraint = (int *)calloc(sizeof(int), board_size);
    int num_of_idexes_for_constraint;

    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            num_of_idexes_for_constraint = get_vars_by_cell(vars, i, j, board_size, num_of_params,
                                                            gurobi_indexes_for_constraint);

            for (k = 0; k < num_of_idexes_for_constraint; k++)
            {
                ind[k] = gurobi_indexes_for_constraint[k];
                val[k] = 1.0;
            }

            add_vectors_to_constraints(model, num_of_idexes_for_constraint, ind, val, env);
        }
    }
    return 1;
}

int add_rows_constraints(Board *board, GRBmodel *model, int *ind, double *val, GRBenv *env,
                         gurobi_var *vars, int num_of_params)
{
    int i;
    int j;
    int k;
    int value_of_constraint;
    int num_of_idexes_for_constraint;
    int board_size = board->num_of_columns * board->num_of_rows;
    int *gurobi_indexes_for_constraint = (int *)calloc(sizeof(int), board_size);

    for (value_of_constraint = 0; value_of_constraint < board_size; value_of_constraint++)
    {
        for (i = 0; i < board_size; i++)
        {

            num_of_idexes_for_constraint = get_vars_by_row(vars, i, board_size, num_of_params,
                                                           gurobi_indexes_for_constraint, value_of_constraint + 1);

            for (k = 0; k < num_of_idexes_for_constraint; k++)
            {
                ind[k] = gurobi_indexes_for_constraint[k];
                val[k] = 1.0;
            }
            add_vectors_to_constraints(model, num_of_idexes_for_constraint, ind, val, env);
        }
    }

    return 1;
}

int add_column_constraints(Board *board, GRBmodel *model, int *ind, double *val, GRBenv *env,
                           gurobi_var *vars, int num_of_params)
{
    int i;
    int j;
    int k;
    int value_of_constraint;
    int num_of_idexes_for_constraint;
    int board_size = board->num_of_columns * board->num_of_rows;
    int *gurobi_indexes_for_constraint = (int *)calloc(sizeof(int), board_size);

    for (value_of_constraint = 0; value_of_constraint < board_size; value_of_constraint++)
    {
        for (i = 0; i < board_size; i++)
        {
            num_of_idexes_for_constraint = get_vars_by_column(vars, i, board_size, num_of_params,
                                                              gurobi_indexes_for_constraint, value_of_constraint + 1);

            for (k = 0; k < num_of_idexes_for_constraint; k++)
            {
                ind[k] = gurobi_indexes_for_constraint[k];
                val[k] = 1;
            }
            add_vectors_to_constraints(model, num_of_idexes_for_constraint, ind, val, env);
        }
    }

    return 1;
}

int add_square_constraints(Board *board, GRBmodel *model, int *ind, double *val, GRBenv *env,
                           gurobi_var *vars, int num_of_params)
{
    int k;
    int i;
    int j;
    int counter = 0;
    int square_index_to_check;
    int value_of_constraint;
    int board_size = board->num_of_columns * board->num_of_rows;
    int num_of_idexes_for_constraint;
    int *gurobi_indexes_for_constraint = (int *)calloc(sizeof(int), board_size);
    int **square_num_matrix = (int **)malloc(sizeof(int *) * board->num_of_columns);

    printf("creating square matrix helper\n");
    for (i = 0; i < board->num_of_columns; i++)
    {
        square_num_matrix[i] = (int *)malloc(sizeof(int) * board->num_of_rows);
        for (j = 0; j < board->num_of_rows; j++)
        {
            square_num_matrix[i][j] = counter;
            ++counter;
        }
    }

    for (value_of_constraint = 0; value_of_constraint < board_size; value_of_constraint++)
    {
        for (square_index_to_check = 0; square_index_to_check < board_size; square_index_to_check++)
        {
            num_of_idexes_for_constraint = get_vars_by_square(vars, square_index_to_check, board, num_of_params,
                                                              gurobi_indexes_for_constraint, value_of_constraint + 1, square_num_matrix);

            for (k = 0; k < num_of_idexes_for_constraint; k++)
            {
                ind[k] = gurobi_indexes_for_constraint[k];
                val[k] = 1;
            }
            add_vectors_to_constraints(model, num_of_idexes_for_constraint, ind, val, env);
        }
    }
    return 1;
}

int update_constraints(Board *board, GRBmodel *model, int *ind, double *val, GRBenv *env, gurobi_var *vars, int num_of_params)
{
    add_single_value_per_cell_constraints(board, model, ind, val, env, vars, num_of_params);

    add_rows_constraints(board, model, ind, val, env, vars, num_of_params);

    add_column_constraints(board, model, ind, val, env, vars, num_of_params);

    add_square_constraints(board, model, ind, val, env, vars, num_of_params);

    return 1;
}

void createBounds(double *lb, double *ub, int num_of_params)
{
    int i;
    for (i = 0; i < num_of_params; i++)
    {
        lb[i] = 0.0;
        ub[i] = 1.0;
    }
}

double *run_LP(Board *board, int params_mode, gurobi_var *vars, int num_of_params)
{

    int i;
    int board_size = board->num_of_columns * board->num_of_rows;
    GRBenv *env = NULL;
    GRBmodel *model = NULL;
    int error = 0;
    double *sol = (double *)malloc(num_of_params * sizeof(double));
    int *ind = (int *)malloc(board_size * sizeof(int));
    double *val = (double *)malloc(board_size * sizeof(double));
    double *obj = (double *)malloc(num_of_params * sizeof(double));
    char *vtype = (char *)malloc(num_of_params * sizeof(char));
    double *lb = (double *)malloc(num_of_params * sizeof(double));
    double *ub = (double *)malloc(num_of_params * sizeof(double));
    int optimstatus;
    double objval;

    createBounds(lb, ub, num_of_params);

    /* Add variables */
    for (i = 0; i < num_of_params; i++)
    {
        /* variable types - for x,y,z (cells 0,1,2 in "vtype") */
        /* other options: GRB_INTEGER, GRB_CONTINUOUS */
        if (params_mode == 1)
        {
            vtype[i] = GRB_BINARY;
        }
        else
        {
            vtype[i] = GRB_CONTINUOUS;
        }

        /* coefficients - for x,y,z (cells 0,1,2 in "obj")
        maximize x+y+z+k.. */
        obj[i] = rand() % (2 * board_size);
    }

    /* Create environment - log file is mip1.log */
    error = GRBloadenv(&env, NULL);
    if (error)
    {
        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error)
    {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    /* Create an empty model named "mip1" */
    error = GRBnewmodel(env, &model, "mip1", num_of_params, obj, lb, ub, vtype, NULL);
    if (error)
    {
        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    error = GRBaddvars(model, num_of_params, 0, NULL, NULL, NULL, obj, lb, ub, vtype, NULL);
    if (error)
    {
        printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    /* Change objective sense to maximization */
    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (error)
    {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    /* update the model - to integrate new variables */

    error = GRBupdatemodel(model);
    if (error)
    {
        printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    update_constraints(board, model, ind, val, env, vars, num_of_params);

    /* Optimize model - need to call this before calculation */
    error = GRBoptimize(model);
    if (error)
    {
        printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    /* Write model to 'mip1.lp' - this is not necessary but very helpful */
    error = GRBwrite(model, "mip1.lp");
    if (error)
    {
        printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    /* Get solution information */

    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error)
    {
        printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
        return NULL;
    }

    if (optimstatus == GRB_OPTIMAL)
    {
        error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
        if (error)
        {
            printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
            return NULL;
        }

        /* get the solution - the assignment to each variable */
        error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, num_of_params, sol);
        if (error)
        {
            printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
            return NULL;
        }
    }

    /* no solution found */
    else if (optimstatus == GRB_INF_OR_UNBD)
    {
        printf("Model is infeasible or unbounded\n");
    }
    /* error or calculation stopped */
    else
    {
        printf("Optimization was stopped early\n");
    }

    /* IMPORTANT !!! - Free model and environment */
    GRBfreemodel(model);
    GRBfreeenv(env);

    if (optimstatus != GRB_OPTIMAL)
        sol = NULL;

    return sol;
}

OptionalCellValues get_possible_values_from_sol(Board *board, double *sol, int row, int column, int threshold,
                                                gurobi_var *vars, int possible_values_size)
{
    int i;
    int num_of_indexes;
    OptionalCellValues cell_values;
    int board_size = board->num_of_columns * board->num_of_rows;
    cell_values.column = column;
    cell_values.row = row;
    cell_values.propabilities = (float *)calloc(sizeof(float), board_size);
    int *gurobi_relevant_indexes = (int *)calloc(sizeof(int), board_size);
    num_of_indexes = get_vars_by_cell(vars, row, column, board_size, possible_values_size, gurobi_relevant_indexes);

    for (i = 0; i < num_of_indexes; i++)
    {
        if(sol[gurobi_relevant_indexes[i]] < threshold)
            continue;
            
        cell_values.propabilities[vars[gurobi_relevant_indexes[i]].possible_value - 1] = sol[gurobi_relevant_indexes[i]];
    }

    return cell_values;
}

int prob_based_decide_result(float *cell_probs, float threshold, int n)
{
    int i;
    /* construct a sum array from given probabilities */
    int prob_sum[n];
    memset(prob_sum, 0, sizeof prob_sum);

    /* prob_sum[i] holds sum of all probability[j] for 0 <= j <=i */
    prob_sum[0] = cell_probs[0] * 100;
    for (i = 1; i < n; i++)
        prob_sum[i] = prob_sum[i - 1] + (cell_probs[i] * 100);

    int r = (rand() % 100) + 1;

    /* based on the comparison result, return corresponding
	 element from the input array */
    if (r <= prob_sum[0]) // handle 0'th index separately
        return 1;

    for (i = 1; i < n; i++)
    {
        if (r > prob_sum[i - 1] && r <= prob_sum[i])
        {
            return i + 1;
        }
    }

    return BOARD_NULL_VALUE;
}

void print_cell_results(OptionalCellValues cell_values, int size)
{
    int k;
    for (k = 0; k < size; k++)
    {
        if (cell_values.propabilities[k] > 0)
        {
            printf("value %d for index %d,%d has prob of %f\n", k + 1, cell_values.row, cell_values.column, cell_values.propabilities[k]);
        }
    }
}

void print_gurobi_results(Board *board, double *sol, float threshold, gurobi_var *vars, int possilbe_values_size)
{
    int i;
    int j;
    int chosen_val;
    int board_size = board->num_of_columns * board->num_of_rows;
    OptionalCellValues cell_values;
    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            cell_values = get_possible_values_from_sol(board, sol, i, j, threshold, vars, possilbe_values_size);
            print_cell_results(cell_values, board_size);
        }
    }
}

void fill_results_to_board(Board *board, double *sol, float threshold, gurobi_var *vars, int num_of_params)
{
    int i;
    int j;
    int chosen_val;
    int set_successful;
    int board_size = board->num_of_columns * board->num_of_rows;
    OptionalCellValues **cell_values = create_2d_possible_values_array(board_size);

    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            cell_values[i][j] = get_possible_values_from_sol(board, sol, i, j, threshold, vars, num_of_params);
            chosen_val = prob_based_decide_result(cell_values[i][j].propabilities, threshold, board_size);

            if (chosen_val != BOARD_NULL_VALUE)
            {
                cell_values[i][j].chosen_value = chosen_val;
            }
            else
            {
                cell_values[i][j].chosen_value = BOARD_NULL_VALUE;
            }
        }
    }

    for (i = 0; i < board_size; i++)
    {
        for (j = 0; j < board_size; j++)
        {
            if (cell_values[i][j].chosen_value != BOARD_NULL_VALUE)
            {
                set_value(i, j, cell_values[i][j].chosen_value, board, 0);
            }
        }
    }
}

void fill_board(Board *board, int is_integer, float threshold)
{
    int status;
    double *sol;
    gurobi_var *vars;
    int i;
    int num_of_params = get_num_of_parameters(board);
    vars = initilize_gurobi_vars(num_of_params, board);
    sol = run_LP(board, is_integer, vars, num_of_params);

    if (sol != NULL)
    {
        fill_results_to_board(board, sol, threshold, vars, num_of_params);
    }
}

OptionalCellValues get_value_for_cell(Board *board, int row, int column, int is_integer)
{
    int i;
    int board_size = board->num_of_columns * board->num_of_rows;
    int chosen_num;
    OptionalCellValues cell_values;
    double *sol;
    gurobi_var *vars;
    int num_of_params = get_num_of_parameters(board);
    vars = initilize_gurobi_vars(num_of_params, board);

    sol = run_LP(board, is_integer, vars, num_of_params);
    if (sol == NULL)
    {
        return cell_values;
    }

    return get_possible_values_from_sol(board, sol, row, column, 0, vars, num_of_params);
}

int validate_ILP(Board *board)
{
    int result;
    double *sol;
    gurobi_var *vars;
    int num_of_params = get_num_of_parameters(board);
    vars = initilize_gurobi_vars(num_of_params, board);
    sol = run_LP(board, 1, vars, num_of_params);
    print_gurobi_results(board, sol, 0.01, vars, num_of_params);
    return sol != NULL;
}