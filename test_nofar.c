#include "soduko_board_actions.h"

int main(){
    Board* b;
    b->num_of_columns = 2;
    b->num_of_rows = 2;
    
    int sol[4][4] = {
    {1, 4, 3, 2},
    {2, 3, 4, 1},
    {4, 2, 1, 3},
    {3, 1, 2, 4}
    };
    b->solved_board = sol;
    
    int fix[4][4] = {
    {1, BOARD_NULL_VALUE, 3, 2},
    {2, 3, BOARD_NULL_VALUE, 1},
    {BOARD_NULL_VALUE, 2, 1, 3},
    {3, 1, 2, BOARD_NULL_VALUE}
    };
    b->fixed_board = fix;

    print_board(b);
}