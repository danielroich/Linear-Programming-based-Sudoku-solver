
#ifndef SOFTWAREPROJ_SODUKO_BOARD_H
#define SOFTWAREPROJ_SODUKO_BOARD_H

struct Board
{
    int** solved_board;
    int** cur_board;
    int*** possible_values;
};


#endif 
