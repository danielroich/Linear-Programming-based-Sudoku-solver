#include "files_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_file_from_board (Board* board, char* path){
    int i,j,size;
    FILE* fptr;
    
    fptr = fopen(path,'w'); 
    if(fptr ==NULL){
        printf("Error: invalid file\n");
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
                if(board->cur_board[i][j] != BOARD_NULL_VALUE){
                    fprintf(fptr,"%d ",board->cur_board[i][j]);
                }
                else
                {
                    fprintf(fptr,"0 ");
                } 
            }
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return 0;
}

int read_file_to_board (Board* board, char* path){
    int row,col,size;
    int value,count,count_scan,count_dot;
    int i,j;
    char ch;
    FILE* fptr;
    
    fptr = fopen(path,'r'); 
    if(fptr ==NULL){
        fclose(fptr);
        return 0;
    }

    count = 0;
    while(!feof(fptr) && count<2){
        count_scan = fscanf(fptr,"%d",&value);
        if(count_scan != 0){
            if(count == 0){
                row = value;
            }
            else {
                col = value;
            }
        }
    }
    if(count<2){
        fclose(fptr);
        return 0;
    }
    
    create_empty_board(board,row,col);
    
    size = row*col; 
    count = 0;
    count_dot = 0;
    i = 0;
    j = 0;

    while(!feof(fptr) && i<size){
        count_scan = fscanf(fptr,"%d",&value); 
        if(!feof(fptr)){
            count_dot = fscanf(fptr,"."); /*sure not another int*/
        }
        if(count_scan != 0){
            if(value > size || value < 1){
                fclose(fptr);
                return 0;
            }
            if(count_dot == 1){
                if(value == 0){
                    board->fixed_board[i][j]=BOARD_NULL_VALUE;
                }
                else{
                    if(is_legal(i,j,value,board,1)){
                        board->fixed_board[i][j]=value;
                    }
                    else{
                        fclose(fptr);
                        return 0;
                    }
                }
            }
            if(value == 0){
                    board->cur_board[i][j]=BOARD_NULL_VALUE;
            }
            else{
                    board->cur_board[i][j]=value;
                    if(count_dot == 0){board->count_filled++;}; /*not fixed*/
            }
            if(j!=size-1){j++;}
            else{i++;j=0;}
        }
    }
    if(i!=size){
        fclose(fptr);
        return 0;
    }
    fclose(fptr);
    return 1;
}