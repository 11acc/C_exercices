
//
// header file for tictactoe.c
// 11acc / alejandro gutierrez acosta

#ifndef TICTACTOE_H
#define TICTACTOE_H

typedef struct {
    char board[9];
    int p1Score;
    int p2Score;
    int currPlayer;
} GameState;

// main game functions
void displayGrid(char b[]);
int checkWin(char b[], char p);
void isValidMove(int *move, char b[]);
void isDraw(int *gC, char b[]);
char checkPlayerOrder(int counter);

// other utility functions
GameState initialiseGame();
void updateNSave(GameState* gameState, int xScore, int oScore, int counter, int win, char b[]);
int loadGame(GameState* gameState);
void clearInputBuffer();

#endif // TICTACTOE_H