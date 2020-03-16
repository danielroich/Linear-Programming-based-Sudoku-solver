#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_fixed(Board* board);
int check_only_digits(const char* path);

/* write current board to path in file format
mark if fixed. if in edit mode all is fixed.*/
int write_file_from_board (Board* board,const char* path){
    int i,j,size;
    FILE* fptr;
    const char* w = "w";
    
    fptr = fopen(path,w); 
    if(fptr ==NULL){
        printf("Error: invalid file.\n");
        return 0;
    }   
    size = board->num_of_rows*board->num_of_columns;
    fprintf(fptr,"%d %d\n",board->num_of_rows,board->num_of_columns); 
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(board->fixed_board[i][j] != BOARD_NULL_VALUE){
                fprintf(fptr,"%d. ",board->fixed_board[i][j]);
            }
            else{
                if(board->cur_board[i][j] != BOARD_NULL_VALUE && board->mode == SOLVE){
                    fprintf(fptr,"%d ",board->cur_board[i][j]);
                }
                else
                {
                    if(board->cur_board[i][j] != BOARD_NULL_VALUE && board->mode == EDIT){
                        fprintf(fptr,"%d. ",board->cur_board[i][j]);
                    }
                    else
                        fprintf(fptr,"0 ");
                } 
            }
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return 0;
}

/* write vaild file to Board
return -1 if didn't create_empty_board
return 0 if not vaild file:
correct format, enough values, correct range, fixed cells are legal*/
int read_file_to_board(Board* board, const char* path, int check_errors){
    int row,col,size;
    int value,count,count_scan,count_dot,count_char;
    int i,j;
    char ch;
    FILE* fptr;
    const char* r = "r";
    int count_dots;

    fptr = fopen(path,r); 
    if(fptr ==NULL){
        printf("Error: the file/path might not exist or could not be opened.\n");
        return -1;
    }
    
    count_dots = check_only_digits(path);
    if(count_dots==-1){
        printf("Error: file contain unwelcome chars.\n");
        fclose(fptr);
        return -1;
    }

    row = 0;
    col = 0;
    count = 0;
    while(!feof(fptr) && count<2){
        count_scan = 0;
        count_scan = fscanf(fptr,"%d",&value);
        if(count_scan == 1){
            if(count == 0){
                row = value;
                count++;
            }
            else {
                col = value;
                count++;
            }
        }
    }
    if(count<2){
        printf("Error: file not in right format.\n");
        fclose(fptr);
        return -1;
    }
    
    create_empty_board(board,row,col);
    
    size = row*col; 
    count_dot = 0;
    count_char = 0;
    i = 0;
    j = 0;

    while(!feof(fptr) && i<size){
        count_scan = 0;
        count_scan = fscanf(fptr,"%d",&value); 
        count_char =0;
        count_dot = 0;
        if(!feof(fptr)){
            count_char = fscanf(fptr,"%c",&ch); /*sure not another int*/
            if(count_char == 1 && ch == '.'){
                count_dot = 1;} 
        }
        if(count_scan == 1){
            if(value > size || value < 0){
                printf("Error: file contain value out of range.\n");
                fclose(fptr);
                return 0;
            }
            if(count_dot == 1){
                if(value == 0){
                    printf("Error: file not in right format.\n");
                    fclose(fptr);
                    return 0;
                }
                else{
                    if(check_errors == 0){
                        board->fixed_board[i][j]=value;
                    }
                    else{
                        if(is_legal(i,j,value,board,1)){
                            board->fixed_board[i][j]=value;
                        }
                        else
                        {
                            printf("Error: fixed cells are ilegal.\n");
                            fclose(fptr);
                            return 0;
                        }
                    }
                }
            }
            if(value == 0){
                    board->cur_board[i][j]=BOARD_NULL_VALUE;
            }
            else{
                    board->cur_board[i][j]=value;
                    board->count_filled++; 
            }
            if(j!=size-1){
                j++;
            }
            else{
                i++;
                j=0;
            }
        }
    }
    if(i!=size){
        printf("Error: file contain not enough values.\n");
        fclose(fptr);
        return 0;
    }
    count_scan = fscanf(fptr,"%d",&value); 
    if(count_scan == 1){
        printf("Error: file contain too many values.\n");
        fclose(fptr);
        return 0;
    }
    if(count_dots != count_fixed(board)){
        printf("Error: file not in right format.\n");
        fclose(fptr);
        return 0;
    }
    fclose(fptr);
    return 1;
}

/* check if there are chars which different than spaces, numbers and dot
return -1 if there is, otherwise return counter of dots in file*/
int check_only_digits(const char* path){
    int count_dots = 0;
    FILE* fptr;
    const char* r = "r";
    char ch;
    unsigned char ch1;

    fptr = fopen(path,r); 
    /*called if opened ok, but to make sure:*/
    if(fptr ==NULL){
        return -1;
    }

    while ((ch=getc(fptr))!=EOF)
     {
        ch1= (unsigned char) ch;  
        if((ch1 < '0' || ch1 > '9') && ch1 != ' ' && ch1 != '\n' && ch1!='\t' && ch1!='\r' && ch1!='.'){
            fclose(fptr);
            return -1;
        }
        if(ch1 == '.'){
            count_dots++;
        }
    }       
    fclose(fptr);
    return count_dots;
}

/* in order to check if equal to counter of dot in file*/
int count_fixed(Board* board){
    int i, j;
    int count = 0;
    int size = (board->num_of_rows)*(board->num_of_columns);
    for (i=0; i<size; i++){
        for (j=0; j<size; j++){
            if(board->fixed_board[i][j]!=BOARD_NULL_VALUE){
                count++;
            }
        }
    }
    return count;
}