#include "files_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int write_file_from_board (Board* board, char* path){
    int i,j,size;
    FILE* fptr;
    
    fptr = fopen(path,'w'); 
    if(fptr ==NULL){
        printf("Error: invalid command\n");
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
    int row,col,size,count,i,j,value;
    char ch;
    FILE* fptr;
    
    fptr = fopen(path,'r'); 
    if(fptr ==NULL){
        printf("Error: invalid command\n");
        return 0;
    }
    count=0;
    while(count<2 && ch != EOF){
        ch = fgetc(fptr);
        if (ch != '\n' && ch != '\t' && ch != '\r' && ch != ' '){
            if(count == 0){
                row = atoi(ch);
                count++;
            }
            else{
                col = atoi(ch);
                count++;
            }
        }
    }
    if(count != 2){
        return 0;
    }
    create_empty_board(board,row,col);
    size = row*col; /*each single digit*/
    i=0;
    j=0;
    while (ch != EOF)
    {
        ch = fgetc(fptr);
        if (ch != '\n' && ch != '\t' && ch != '\r' && ch != ' '){
            value = atoi(ch);
            if(ch != EOF){
                ch = fgetc(fptr); /* what if two digits in cell? */
                if(ch == '.'){
                    board->fixed_board[i][j]=value;
                }
                else{
                    if(value == 0){
                        board->cur_board[i][j]=BOARD_NULL_VALUE;
                    }
                    else{
                        board->cur_board[i][j]=value;
                    }
                }
                if(j!=size-1){j++;}
                else{i++;j=0;}
                if(i==size+1){fclose(fptr); return 0;}
            }
            
        }
    } 

    fclose(fptr);
    return 0;
}