//
// Created by Daniel on 12/21/2019.
//

#ifndef SOFTWAREPROJ_SODUKO_BOARD_H
#define SOFTWAREPROJ_SODUKO_BOARD_H

typedef struct board
{
    int [][] solved_baord;
    int [][] cur_board;
    int [][][] possible_values;
} Board;


#endif //SOFTWAREPROJ_SODUKO_BOARD_H
