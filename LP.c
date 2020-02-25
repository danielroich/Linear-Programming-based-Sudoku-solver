#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LP.h"
#include "gurobi_c.h"
#include "backtrack_core.h"
#include <math.h>

int get_num_of_parameters(Board* board) {
    int i;
    int j;
    int counter = 0;
    int* possible_values = (int*)calloc(board->num_of_columns * board->num_of_rows, sizeof(int));
    for (i = 0; i < board->num_of_rows; i++)
    {
        for (j = 0; j < board->num_of_columns; j++)
        {
            if (get_value(i,j,board,0) != BOARD_NULL_VALUE)
            {
                counter += get_possible_values(board,i,j,possible_values);
            }   
        }
    }
    return counter;
}

int add_single_value_per_cell_constraints(Board* board, GRBmodel *model, int *ind, double *val, GRBenv *env) {
    int i;
    int j;
    int k;
    char i_char[4096];
    int error = 0;
    char unique_name[2048] = "a";
    int counter = 0;
    int chars_to_copy;
    int* possible_values = (int*)calloc(board->num_of_columns * board->num_of_rows, sizeof(int));
    int possible_value_size;
    for (i = 0; i < board->num_of_rows; i++)
    {
        for (j = 0; j < board->num_of_columns; j++)
        {
            possible_value_size = get_possible_values(board,i,j, possible_values);

            if (possible_value_size == -1)
                continue;

            for (k = 0; k < possible_value_size; k++)
            {
                ind[k] = k + counter;
                val[k] = 1;
                counter++;
            }

            /* generate unique name by concatinating i value to the unique name string */
            chars_to_copy = (int)((ceil(log10(i))+1)*sizeof(char));
            sprintf(i_char, "%d",chars_to_copy);
            strcat(unique_name,i_char);

            error = GRBaddconstr(model, possible_value_size, ind, val, GRB_EQUAL,1, unique_name);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                return -1;
            }

            /* clean the data */
            for (k = 0; k < possible_value_size; k++)
            {
                ind[k] = 0;
                val[k] = 0;

            }
        }
    }
    return 1;
}

int add_rows_constraints(Board* board, GRBmodel *model, int *ind, double *val, GRBenv *env) {
    int i;
    int j;
    int k;
    int index_in_row;
    char i_char[4096];
    int val_written = 0;
    int board_size = board->num_of_columns * board->num_of_rows;
    int error = 0;
    int optional_occurences = 0;
    char unique_name[2048] = "b";
    int counter = 0;
    int chars_to_copy;
    int* possible_values = (int*)calloc(board_size, sizeof(int));
    int possible_value_size;
    for (i = 0; i < board->num_of_rows; i++)
    {
        for (index_in_row = 0; index_in_row < board_size; index_in_row++)
        {
            for (j = 0; j < board->num_of_columns; j++)
            {
                possible_value_size = get_possible_values(board,i,j, possible_values);

                if (possible_value_size == -1)
                    continue;

                for (k = 0; k < possible_value_size; k++)
                {
                    if (possible_values[index_in_row] == 1 && val_written == 0)
                    {
                        val_written = 1;
                        ++optional_occurences;
                        ind[k] = k + counter;
                        val[k] = 1;
                    }   
                    counter++;
                }

                val_written = 0;
            }     

            if(optional_occurences == 0)
                continue;

            /* generate unique name by concatinating i value to the unique name string */
            chars_to_copy = (int)((ceil(log10(i))+1)*sizeof(char));
            sprintf(i_char, "%d",chars_to_copy);
            strcat(unique_name,i_char);

            error = GRBaddconstr(model, optional_occurences, ind, val, GRB_EQUAL, 1, unique_name);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                return -1;
            }

            /* clean the data */
            for (k = 0; k < optional_occurences; k++)
            {
                ind[k] = 0;
                val[k] = 0;

            }         
        } 
    }

    return 1;
}

int add_column_constraints(Board* board, GRBmodel *model, int *ind, double *val, GRBenv *env) {
    int i;
    int j;
    int k;
    int index_to_check;
    char i_char[4096];
    int board_size = board->num_of_columns * board->num_of_rows;
    int error = 0;
    int optional_occurences = 0;
    char unique_name[2048] = "c";
    int counter = 0;
    int val_written = 0;
    int chars_to_copy;
    int column_to_check;
    int* possible_values = (int*)calloc(board_size, sizeof(int));
    int possible_value_size;
     for (index_to_check = 0; index_to_check < board_size; index_to_check++)
     {
         for (column_to_check = 0; column_to_check < board->num_of_columns; column_to_check++)
         {
            for (i = 0; i < board->num_of_rows; i++) {

                for (j = 0; j < board->num_of_columns; j++)
                {
                    possible_value_size = get_possible_values(board,i,j, possible_values);

                    if (possible_value_size == -1)
                        continue;

                    for (k = 0; k < possible_value_size; k++)
                    {
                        if (j == column_to_check && possible_values[index_to_check] == 1 && val_written == 0)
                        {
                            val_written = 1;
                            ++optional_occurences;
                            ind[k] = k + counter;
                            val[k] = 1;
                        }   
                        counter++;
                    }

                    val_written = 0;
                }     
            }

            if(optional_occurences == 0)
                    continue;

            /* generate unique name by concatinating i value to the unique name string */
            chars_to_copy = (int)((ceil(log10(i))+1)*sizeof(char));
            sprintf(i_char, "%d",chars_to_copy);
            strcat(unique_name,i_char);

            error = GRBaddconstr(model, optional_occurences, ind, val, GRB_EQUAL, 1, unique_name);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                return -1;
            }

            /* clean the data */
            for (k = 0; k < optional_occurences; k++)
            {
                ind[k] = 0;
                val[k] = 0;

            }  
         }
    }
    return 1;
}

int add_square_constraints(Board* board, GRBmodel *model, int *ind, double *val, GRBenv *env) {
    int i;
    int j;
    int k;
    int index_to_check;
    char i_char[4096];
    int board_size = board->num_of_columns * board->num_of_rows;
    int error = 0;
    int optional_occurences = 0;
    char unique_name[2048] = "d";
    int counter = 0;
    int val_written = 0;
    int chars_to_copy;
    int value_to_check;
    int top_left_corner_row;
    int top_left_corner_col;
    int **square_num_matrix = (int**) malloc(sizeof(int*) * board->num_of_columns);
    for (i = 0; i < board->num_of_rows; i++)
    {
        square_num_matrix[i] = (int*) malloc(sizeof(int) * board->num_of_rows);
        for (j = 0; i < board->num_of_rows; i++)
        {
            square_num_matrix[i][j] = counter;
            ++counter;
        }     
    }
    counter = 0;
    
    int* possible_values = (int*)calloc(board_size, sizeof(int));
    int possible_value_size;
     for (index_to_check = 0; index_to_check < board_size; index_to_check++)
     {
         for (value_to_check = 0; value_to_check < board->num_of_columns; value_to_check++)
         {
            for (i = 0; i < board->num_of_rows; i++) {

                for (j = 0; j < board->num_of_columns; j++)
                {
                    possible_value_size = get_possible_values(board,i,j, possible_values);

                    if (possible_value_size == -1)
                        continue;

                    top_left_corner_row = floor(i/board->num_of_rows)*board->num_of_rows; 
                    top_left_corner_col = floor(j/board->num_of_columns)*board->num_of_columns; 

                    for (k = 0; k < possible_value_size; k++)
                    {
                        if (square_num_matrix[(top_left_corner_row / board->num_of_columns)][(top_left_corner_col / board->num_of_rows)]
                         == index_to_check && possible_values[value_to_check] == 1 && val_written == 0)
                        {
                            val_written = 1;
                            ++optional_occurences;
                            ind[k] = k + counter;
                            val[k] = 1;
                        }   
                        counter++;
                    }

                    val_written = 0;
                }     
            }

            if(optional_occurences == 0)
                    continue;

            /* generate unique name by concatinating i value to the unique name string */
            chars_to_copy = (int)((ceil(log10(i))+1)*sizeof(char));
            sprintf(i_char, "%d",chars_to_copy);
            strcat(unique_name,i_char);

            error = GRBaddconstr(model, optional_occurences, ind, val, GRB_EQUAL, 1, unique_name);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                return -1;
            }

            /* clean the data */
            for (k = 0; k < optional_occurences; k++)
            {
                ind[k] = 0;
                val[k] = 0;

            }  
         }
    }
    return 1;
}

int validate(Board* board) {
    int i;
    int num_of_params = get_num_of_parameters(board);
    int board_size = board->num_of_columns * board->num_of_rows;
    GRBenv   *env   = NULL;
    GRBmodel *model = NULL;
    int       error = 0;
    double    *sol = (double*) malloc(num_of_params * sizeof(double));
    int       *ind = (int*) malloc(board_size * sizeof(int));
    double    *val = (double*) malloc(board_size * sizeof(double));
    double    *obj = (double*) malloc(num_of_params * sizeof(double));
    char      *vtype = (char*) malloc(num_of_params * sizeof(char));
    int       optimstatus;
    double    objval;

    /* Create environment - log file is mip1.log */
  error = GRBloadenv(&env, "mip1.log");
  if (error) {
	  printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }
  
  error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
  if (error) {
	  printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* Create an empty model named "mip1" */
  error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
  if (error) {
	  printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* Add variables */
  for (i = 0; i < num_of_params; i++)
  {
      /* variable types - for x,y,z (cells 0,1,2 in "vtype") */
      /* other options: GRB_INTEGER, GRB_CONTINUOUS */
      vtype[i] = GRB_BINARY;

      /* coefficients - for x,y,z (cells 0,1,2 in "obj")
        maximize x+y+z+k.. */
      obj[i] = 1;
  }
  
  /* add variables to model */
  error = GRBaddvars(model, num_of_params, 0, NULL, NULL, NULL, obj, NULL, NULL, vtype, NULL);
  if (error) {
	  printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* Change objective sense to maximization */
  error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
  if (error) {
	  printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* update the model - to integrate new variables */

  error = GRBupdatemodel(model);
  if (error) {
	  printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }


  add_single_value_per_cell_constraints(board,model,ind,val, env);

  add_rows_constraints(board,model,ind,val, env);

  add_column_constraints(board,model,ind,val, env);

  add_square_constraints(board,model,ind,val, env);

  /* Optimize model - need to call this before calculation */
  error = GRBoptimize(model);
  if (error) {
	  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* Write model to 'mip1.lp' - this is not necessary but very helpful */
  error = GRBwrite(model, "mip1.lp");
  if (error) {
	  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* Get solution information */

  error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
  if (error) {
	  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* get the objective -- the optimal result of the function */
  error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
  if (error) {
	  printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* get the solution - the assignment to each variable */
  /* 3-- number of variables, the size of "sol" should match */
  error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, num_of_params, sol);
  if (error) {
	  printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
	  return -1;
  }

  /* print results */
  printf("\nOptimization complete\n");
  
  /* solution found */
  if (optimstatus == GRB_OPTIMAL) {
    printf("Optimal objective: %.4e\n", objval);
    printf("  x=%.2f, y=%.2f, z=%.2f\n", sol[0], sol[1], sol[2]);
  }
  /* no solution found */
  else if (optimstatus == GRB_INF_OR_UNBD) {
    printf("Model is infeasible or unbounded\n");
  }
  /* error or calculation stopped */
  else {
    printf("Optimization was stopped early\n");
  }

  /* IMPORTANT !!! - Free model and environment */
  GRBfreemodel(model);
  GRBfreeenv(env);

  return 0;
}