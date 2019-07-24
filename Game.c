//
// Created by Rubit on 23/07/2019.
//

#include "Game.h"
#include "MainAux.h"
#include "SPBufferset.h"
#include <stdio.h>
/*
 * returns 1 if the board is filled with numbers in range (1,nm)
 */
int boardIsFilled(Board *gameBoard,int m,int n) {
    int i =0;
    int j=0;
    for ( i = 0; i < m * n; i++) {
        for ( j = 0; j < m * n; j++) {
            if ((*gameBoard).board[i][j].value == 0) {
                return 0;
            }
        }
    }
    (*gameBoard).isSolved = 1;
    return 1;
}
/*
 * marks every cell that has a conflict with cell row,col
 * returns 1 if there exists an erroneous cell
 */
int markErrors(Board *b, int m, int n, int row, int col) {
    int hasErrors =0;
    Cell **board = (*b).board;
    int i=0,j=0,startRow=0,startCol=0;

    int value = board[row][col].value;
    /*
     * mark every identical value in row
     */
    for (i = 0; i < m * n; i++) {
        if (i != col && board[row][i].value == value) {
            board[row][i].marked = 1;
            board[row][col].marked = 1;
            hasErrors =1;
        }
    }

    /*
     * mark every identical value in col
     */
    for (j = 0; j < m * n; j++) {
        if (j != row && board[j][col].value == value) {
            board[j][col].marked = 1;
            board[row][col].marked = 1;
            hasErrors =1;
        }
    }

    startRow = row - row % m;
    startCol = col - col % n;
    /*
     * mark every identical value in square
     */
    for ( i = startRow; i < startRow + m; i++) {
        for ( j = startCol; j < startCol + n; j++) {
            if (i != row && j != col && board[i][j].value == value) {
                board[i][j].marked = 1;
                board[row][col].marked = 1;
                hasErrors =1;
            }
        }
    }
    return hasErrors;

}
/*
 * marks every cell with an error.
 * returns 1 if there exists an erroneous cell
 */
int markBoard(Board *b, int m, int n) {
    int i, j;
    int boardIsErroneous;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if(markErrors(b, m, n, i, j)==1){
                boardIsErroneous =1;
            }
        }
    }
    return boardIsErroneous;
}

void unMarkBoard(Board *b, int m, int n){
    int i,j;
    for( i=0;i<m;i++){
        for(j=0;j<n;j++){
            (*b).board[i][j].marked=0;
                }
            }

}
/*
 * sets the mark_errors field to x
 */
void mark_errors(Board *b, int x){
    (*b).markErrors = x;
}
/*
 * sets the value in position row,col to the value that was given
 */
void set(int x, int y, int z, Board *gameBoard) {
    SP_BUFF_SET();
    /*
     * if the game is solved- set is an invalid command and we will return an error
     */
    if ((*gameBoard).mode == 0) {
        ErrorPrinting(INVALIDCOMMAND, "set");
        return;
    }

    if ((*gameBoard).mode == 2 && (*gameBoard).board[x][y].fixed) {
        ErrorPrinting(FIXEDCELL, "set");
        return;
    }
    (*gameBoard).board[x][y].value = z;


    /*
           * ******************************************
           * ************needs to be fixed*************
           * ******************************************
           */
    print_board(gameBoard, 9, 9);
    if ((*gameBoard).mode==2 && boardIsFilled(gameBoard,9,9)) {
        if(markBoard(gameBoard,9,9) == 1){
            printf("The solution is erroneous");
            unMarkBoard(gameBoard,9,9);
            return;
        }
        printf("Puzzle solved successfully\n");
        (*gameBoard).mode =0;
    }

    return;
}
int save(Board *b, int m, int n, char *path){
    int i,j,value;
    FILE *fptr_out = fopen(path,w);
    if((*b).mode==0 || fptr_out == NULL){
        ErrorPrinting(INVALIDCOMMAND,"save");
        return 0;
    }
    unMarkBoard(b,m,n);
    if((*b).mode == 1 || ((*b).mode == 2 && (*b).markErrors ==1) ) {
        markBoard(b,m,n);
    }
    if(fprintf(fptr_out,"%d",m) < 0 ||
    fprintf(fptr_out,"%c",' ') <0||
    fprintf(fptr_out,"%d",n)<0 ||
    fprintf(fptr_out,"%c",'\n')<0){
        ErrorPrinting(WRITEFILE,"save");
        return 0;
    }
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            value = (*b).board[i][j].value;
            if(fprintf(fptr_out,"%d",value) < 0 ||
            ((*b).board[i][j].fixed==1 && fprintf(fptr_out,"%c",'.') < 0) ||
            ((*b).board[i][j].marked==1 && fprintf(fptr_out,"%c",'*') < 0) ||
            (fprintf(fptr_out,"%c",' ') < 0)){
                ErrorPrinting(WRITEFILE,"save");
                return 0;
            }
        }
        if(fprintf(fptr_out,"%c",'\n') < 0){
            ErrorPrinting(WRITEFILE,"save");
            return 0;
        }
    }
    fclose(fptr_out);
    if(feof(fptr_out)){
        ErrorPrinting(WRITEFILE,"save");
        return 0;
    }
    return 1;
}
int edit(Board *b, char *path){

}

