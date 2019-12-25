#include <stdio.h>

int const BOARD_NULL_VALUE = 0;

typedef struct _Board {
    int num_of_rows; /*in block*/
    int num_of_columns; /*in block*/ 
    int count_filled;
    int** solved_board;
    int** fixed_board;
    int** cur_board;
} Board;

int get_value(int x, int y, Board* board){
    return (board->cur_board)[x][y];
}

void print_board(Board* board){
    int a, b, c, d;
    int row, col, value;
    for(a = 0; a < board->num_of_columns; a++){ 
        printf("----------------------------------\n"); 
        for(b = 0; b < board->num_of_rows; b++){
            row = b + a*(board->num_of_rows);
            printf("| ");
            for(c = 0; c < board->num_of_rows; c++){
                for(d = 0; d < board->num_of_columns; d++){
                    col = d + c*board->num_of_columns;
                    value = get_value(row,col,board);
                    if(board->fixed_board[row][col] != BOARD_NULL_VALUE){
                        printf(".%d ",value);
                    }
                    else{
                        if(value != BOARD_NULL_VALUE)
                            printf(" %d ",value);
                        else
                            printf("   ",value);
                    }
                }
                if(c != (board->num_of_rows-1))
                    printf("| ");
            }
            printf("|\n");
        }     
    }
    printf("----------------------------------\n");
}

int main(){
    Board* board;
    board->num_of_columns = 2;
    board->num_of_rows = 2;
    
    int sol[4][4] = {
    {1, 4, 3, 2},
    {2, 3, 4, 1},
    {4, 2, 1, 3},
    {3, 1, 2, 4}
    };
    for(int i=0;i<4;i++)
       board->solved_board[i]=sol[i]; 

    int fix [4][4]= {
    {1, BOARD_NULL_VALUE, 3, 2},
    {2, 3, BOARD_NULL_VALUE, 1},
    {BOARD_NULL_VALUE, 2, 1, 3},
    {3, 1, 2, BOARD_NULL_VALUE}
    };

    for(int i=0;i<4;i++)
       board->fixed_board[i]=fix[i]; 
    for(int i=0;i<4;i++)
       board->cur_board[i]=fix[i]; 

    printf("hey");

}