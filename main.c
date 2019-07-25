#include <stdio.h>
#include "Game.h"
#include <stdlib.h>
#include "SPBufferset.h"
#include "MainAux.h"

int main() {
    int m=3;
    int n=3;
    Board* b;
    b = (Board*) calloc(1, sizeof(Board));
    b->mode = 1;
    b->board[0][1].value=1;
    b->board[0][1].fixed=1;
    b->board[2][1].value=8;
    b->board[6][6].value=7;
    b->board[7][5].value=1;
    b->board[5][5].value=9;
    b->board[5][5].marked=9;
    b->board[0][7].value=1;
    b->board[0][7].fixed=1;
    b->board[4][8].value=4;
    b->board[3][5].value=2;
    b->board[3][5].marked=1;
    print_board(b,  m,  n);
    return 0;

}
