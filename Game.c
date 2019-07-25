
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

int isErroneous(Board *b, int m, int n){
    int i=markBoard(b,  m,  n);
    unMarkBoard(b, m,  n);
    return i;

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
    struct Action* newAction;
    int arr[3];

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
    arr[0]=x;
    arr[1]=y;
    arr[2]= getValue(gameBoard, x, y);
    SP_BUFF_SET();
    newAction->command=SET;
    newAction->arg=arr;
    newAction->prev=gameBoard->actionP;
    /*need to free memory from p.next to the end of the list */
    ((gameBoard)->actionP)->next=newAction;
    gameBoard->actionP=newAction;

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



/*Ellie*/


void autofill(Board *gameBoard, int m, int n){
    Board* copy;
    int singleValue;
    struct Action* newAction;
    int row;
    int col;
    SP_BUFF_SET();

    if ((*gameBoard).mode == 0 || (*gameBoard).mode == 1) {
        ErrorPrinting(INVALIDCOMMAND, "autofill");
        return;
    }
    if(isErroneous(gameBoard, m, n)){
        /*maybe a different error*/
        ErrorPrinting(INVALIDCOMMAND, "autofill");
        return;
    }

    newAction->command=AUTOFILL;
    newAction->prev=gameBoard->actionP;
    /*need to free memory from p.next to the end of the list */
    ((gameBoard)->actionP)->next=newAction;
    gameBoard->actionP=newAction;

    copyBoard(gameBoard,copy,  m,  n);
    for ( row = 0; row < n*m; row++) {
        for (col = 0; col < n*m; col++) {
            singleValue=singleValidValue(copy, row, col,  m,  n);
            if((*gameBoard).board[row][col].value==0 && singleValue!=-1){
                set(row,col, singleValue, gameBoard);

            }
        }
    }

}


/*
 * getters and setters
 */
int getValue(Board *b, int row, int col) {
    return ((*b).board)[row][col].value;
}
void setValue(Board *b, int row, int col, int val) {
    (*b).board[row][col].value = val;
}

int getNumOfOptions(Board *b, int row, int col) {
    return (*b).board[row][col].numOfOptions;
}
void addOptions(Board *b, int row, int col, int val) {
    int numOfop = (*b).board[row][col].numOfOptions;
    (*b).board[row][col].options[numOfop] = val;
}
void setNumOfOptions(Board *b, int row, int col, int num) {
    (*b).board[row][col].numOfOptions = num;
}

int getOptionInIndex(Board *b, int row, int col, int index) {
    return (*b).board[row][col].options[index];
}

int isFixed(Board *b, int row, int col) {
    return (*b).board[row][col].fixed;
}
void setFixed(Board* b,int row,int col, int i) {
    (*b).board[row][col].fixed = i;
}


int isMarked(Board *b, int row, int col) {
    return (*b).board[row][col].marked;
}
void setMarked(Board* b,int row,int col, int i) {
    (*b).board[row][col].marked = i;

}

/*
 * checks if the value in row,col is a valid value for our game board
 */
int valid(Board *b, int row, int col, int m, int n) {
    Cell **board = (*b).board;
    int i=0,j=0,startRow=0,startCol=0;

    int value = board[row][col].value;
    /*
     * makes sure that the value doesn't exists in row
     */
    for (i = 0; i < m*n; i++) {
        if (i != col && board[row][i].value == value) {
            return 0;
        }
    }

    /*
     * makes sure that the value doesn't exists in col
     */
    for (j = 0; j < m*n; j++) {
        if (j != row && board[j][col].value == value) {
            return 0;
        }
    }

    startRow = row - row % m;
    startCol = col - col % n;
    /*
     * makes sure that the value doesn't exists in square
     */
    for ( i = startRow; i < startRow + m; i++) {
        for ( j = startCol; j < startCol + n; j++) {
            if (i != row && j != col && board[i][j].value == value) {
                return 0;
            }
        }
    }

    return 1;

}
/*
    * if there ia a single valid value , return the value. else return -1.
    * the value of the cell is 0 before and after
    */
 int singleValidValue(Board *b, int row, int col, int m, int n){
    int i;
    int sum=0;
    int value;
    for (i=1;i<n*m+1; i++){
        set(row, col,i, b);
        if(valid(b, row,  col, m, n)){
            if(sum==0){
                sum+=1;
                value=i;
            }
            else{
                return -1;
            }
        }
    }
    set(row, col,0, b);
    return value;


}
void copyBoard(Board *gameBoard, Board* copy, int m, int n) {
    int i=0;
    int j =0;
    for ( i = 0; i < m*n; i++) {
        for ( j = 0; j < m*n; j++) {
            (*copy).board[i][j].value = (*gameBoard).board[i][j].value;
        }
    }

}

