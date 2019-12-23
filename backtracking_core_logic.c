
#include "soduko_board.h"
#include <math.h>

int back_track(Board* board, int is_deterministic) {
    int i;
    int is_sol_found;
    int** solved_boared;

    // Create 2D array to contain the sudoku and change it
    // Created to not change the current board iff the Sol does not exist
    solved_boared = (int **) calloc(board->num_of_rows * sizeof(int *)); 
    for (i=0; i< board->num_of_rows; i++) 
         solved_boared[i] = (int*) calloc(board->num_of_columns * sizeof(int));

    if (is_deterministic == 0)
    {
        is_sol_found = deterministic_back_tracking(board, 0, 0);
    }
    else {
        is_sol_found = randomized_back_tracking(board);
    }
    
    if (is_sol_found) {
        board ->solved_board = solved_boared;
    }

    return is_sol_found;
}

int deterministic_back_tracking(Board* board, int x, int y) {
    int i;
    int possible_values_num;
    int board_rows = board->num_of_rows;
    int board_columns = board->num_of_columns;
    int is_successful;
    int is_set_successfull;

    // If this statement is true we have covered all the boared with values
    // this indicates we have placed the entire boared with values in have finished solving it
    if ( x == board->num_of_rows)
        return 1;

    if (board->cur_board[x][y] != 0)
    {
        advance_in_sudoku(board,x,y);
    }
    
    else {
        possible_values_num = sqrt(board->num_of_columns);

        // the possible values is a vector, and each tried number will be lit with 1
        int* possible_values = (int*) calloc(sqrt(board->num_of_columns) * sizeof(int));

        for (i = 1; i < (possible_values_num + 1); i++)
        {
            is_set_successfull = set_value(x,y,i,board);

            if (is_set_successfull) {
                is_successful = advance_in_sudoku(board,x,y);
            }
            else {
                continue;
            }
            
            if (is_successful)
                return 1;
        }
        
        set_value(x,y, BOARD_NULL_VALUE ,board);
        return 0;
    }
    

  

    // TODO: free tried values
}
int advance_in_sudoku(Board* board, int x, int y) {

}

int randomized_back_tracking(Board* board) {
    
}