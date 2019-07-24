//
// Created by Rubit on 23/07/2019.
//
#include "MainAux.h"
#include "SPBufferset.h"
#include <stdlib.h>


/*
 * gets an enum error and calls the right function
 */
void ErrorPrinting(enum Errors error, char funcName[]) {
    SP_BUFF_SET()
            ;
    switch (error) {
        case MEMORYALLOCATION:
            printf("Error: %s has failed\n", funcName);
            break;
        case INVALIDCELLSNUMBER:
            printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
            break;
        case FEOF:
            printf("Exiting...\n");

            break;
        case FIXEDCELL:
            printf("Error: cell is fixed\n");
            break;
        case INVALIDVALUE:
            printf("Error: value is invalid\n");
            break;
        case INVALIDCOMMAND:
            printf("Error: invalid command\n");
            break;
        case WRITEFILE:
            printf("Error in writing to file \n");
            break;
        case READFILE:
            printf("Error in reading from file\n");
            break;
    }

}
void print_board(Board *b, int m, int n){
    if((*b).mode==0){
        /*
         * vat to do??
         */
    }
    if((*b).mode == 1 || ((*b).mode == 2 && (*b).markErrors ==1) ) {
        markBoard(b, m, n);
    }
        /*
         * add printing function
         */
        unMarkBoard(b,m,n);
}


