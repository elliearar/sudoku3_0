//
// Created by Rubit on 23/07/2019.
//

#ifndef SUDOKU2_0_GAME_H
#define SUDOKU2_0_GAME_H
enum Command {
    SET, HINT, VALIDATE, RESTART, EXIT
};
typedef struct {
    int value;
    int fixed;
    int numOfOptions;
    int *options;
    int marked;
} Cell;
struct Action{
    enum Command command;
    int arg[3];
    struct Action *next;

};

typedef struct {
    Cell **board;
    int isSolved;
    int markErrors;
    /*
     * mode == 0 - init mode
     * mode == 1 - edit mode
     * mode == 2 - solve mode
     */
    int mode;
    struct Action actions;
}Board;

int markErrors(Board *b, int m, int n, int row, int col);
int boardIsFilled(Board *gameBoard,int m,int n);
int markBoard(Board *b, int m, int n);
void unMarkBoard(Board *b, int m, int n);
void mark_errors(Board *b, int x);
int save(Board *b, int m, int n, char *path);
#endif //SUDOKU2_0_GAME_H
