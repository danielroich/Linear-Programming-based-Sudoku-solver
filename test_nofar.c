#include <stdio.h>
#include <math.h> 
int const BOARD_NULL_VALUE = 0;

typedef struct _Board {
    int num_of_rows; /*in block*/
    int num_of_columns; /*in block*/ 
    int count_filled;
    int solved_board[4][4];
    int fixed_board[4][4];
    int cur_board[4][4];
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
                    
                    //printf("%d",value);

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

int value_in_row(int row, int value, Board* board){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
         if(get_value(row,i,board) == value)
            return 1;
    }
    return 0;
}

int value_in_col(int col, int value, Board* board){
    int i;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
         if(get_value(i,col,board) == value)
            return 1;
    }
    return 0;
}

int value_in_square(int row, int col, int value, Board* board){
    int i,j;
    int top_left_corner_row = floor(row/board->num_of_rows)*board->num_of_rows; 
    int top_left_corner_col = floor(col/board->num_of_columns)*board->num_of_columns; 
    for(i= top_left_corner_row; i<board->num_of_rows; i++){
        for(j= top_left_corner_col; j<board->num_of_columns; j++){
            if(get_value(i,j,board) == value)
                return 1;
        }
    }
    return 0;
} 

int set_value(int x, int y, int value, Board* board){
    if((value_in_row(x,value,board) || value_in_col(y,value,board) || value_in_square(x,y,value,board) ))
        return 0;     
    board->cur_board[x][y] = value;
    board->count_filled++;
    return 1;
}

int set_value_user(int x, int y, int value, Board* board){
    if((board->fixed_board)[x-1][y-1] != BOARD_NULL_VALUE){
        printf("Error: cell is fixed\n");
        return 0;
    }
    if(value == 0){
        board->cur_board[x-1][y-1] = BOARD_NULL_VALUE;
        board->count_filled--;
        print_board(board);
        return 0;
    }
    if(set_value(x-1,y-1,value,board) == 0){
            printf("Error: value is invalid\n");
            return 0;
    }
    /* else value was set and count++ in func */    
    print_board(board);
    return 1;
}


int main(){
    printf("hey\n");

    Board board;
    board.num_of_columns = 2;
    board.num_of_rows = 2;
    
    int sol[4][4] = {
    {1, 4, 3, 2},
    {2, 3, 4, 1},
    {4, 2, 1, 3},
    {3, 1, 2, 4}
    };
    int fix [4][4]= {
    {1, BOARD_NULL_VALUE,  BOARD_NULL_VALUE, 2},
    {2, 3, BOARD_NULL_VALUE, 1},
    {BOARD_NULL_VALUE, 2, 1, 3},
    {3, BOARD_NULL_VALUE, BOARD_NULL_VALUE, BOARD_NULL_VALUE}
    };
    int curr [4][4]= {
    {1, 4,  BOARD_NULL_VALUE, 2},
    {2, 3, BOARD_NULL_VALUE, 1},
    {BOARD_NULL_VALUE, 2, 1, 3},
    {3, BOARD_NULL_VALUE, BOARD_NULL_VALUE, BOARD_NULL_VALUE}
    };
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            board.fixed_board[i][j]=fix[i][j];
            board.cur_board[i][j]=curr[i][j];
            board.solved_board[i][j]=sol[i][j];
        }    
    }
    print_board(&board);
    set_value_user(4,4,2,&board);//error in col
    set_value_user(2,3,3,&board);//error in row
    set_value_user(4,3,1,&board);//error in block
    set_value_user(1,1,2,&board);//error to fix
    set_value_user(1,2,0,&board);//clear cell
    set_value_user(2,3,4,&board);//good set

} 