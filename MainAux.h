

#ifndef SUDOKU2_0_MAINAUX_H
#define SUDOKU2_0_MAINAUX_H

#include "Game.h"


enum Errors {
    MEMORYALLOCATION,
    INVALIDCELLSNUMBER,
    FEOF,
    FIXEDCELL,
    INVALIDVALUE,
    INVALIDCOMMAND,
    WRITEFILE,
    READFILE
};
void ErrorPrinting(enum Errors error, char funcName[]);
void print_board(Board *b, int m, int n);

