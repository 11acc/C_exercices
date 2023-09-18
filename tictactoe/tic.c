
//
// program that lets 2 players play tic tac toe
// 11acc

#include <stdio.h>
#include <string.h>

void gameMain(char moveType, int *fScore, int *sScore, int *gameState, int *switchVal);

void inputCheck(int *in);
void clearInputBuffer();
void slctFPlayer(int inputVal, char *moveType, int *switchVal);

void makeBoard(char b[]);
void moveInCheck(int *in, char *boardVals);
void makeAMove(char firstPM, char *boardVals);

int checkWin(char *b, char moveType, int *aScore);


/* ----------- xxx ----------- */


int main() {
    // prompt user
    printf("\nWelcome to Tic-Tac-Toe in C\n");

    int inputVal, fScore=0, sScore=0, gameState=1, switchVal, again=-1;
    int *ptIntVal = &inputVal;
    printf("Choose your mark (X: 0 | O: 1)\n");
    inputCheck(ptIntVal);

    char moveType = ' ';
    slctFPlayer(inputVal, &moveType, &switchVal);

    // main game loop
    do {
        gameState = 1;
        // start of the game
        gameMain(moveType, &fScore, &sScore, &gameState, &switchVal);

        // repeat?
        printf("Want to play again? (y: 0, n: 1)\n");
        inputCheck(&again);
        if (again) {
            gameState = 0;
        }
        printf("\n\n");
    } while (gameState);

    return 11;
}

// -------- ··· --------

void gameMain(char moveType, int *fScore, int *sScore, int *gameState, int *switchVal) {
    int gameActive = 1, win = 0;
    int *aScore;

    // Initialise game
    printf("Score: %d | %d\n", *fScore, *sScore);
    printf("First player: %c\n", moveType);
    // make board
    char boardVals[] = "         "; //empty

    do {
        makeBoard(boardVals);
        // if board doesn't have any spaces
        if (strchr(boardVals, ' ') == NULL) {
            printf("Tie!\n");
            gameActive = 0;
            break;
        }
        // prompt first player to make a move + check
        makeAMove(moveType, boardVals);
        makeBoard(boardVals);
        // Point to current player score
        if (*switchVal % 2 == 0) {
            // normally this would be &fScore, but since its a func pointer...
            aScore = fScore;
        } else {
            aScore = sScore;
        }
        win = checkWin(boardVals, moveType, aScore);
        
        if (win) {
            gameActive = 0;
        }
        *switchVal += 1;

        if (*switchVal % 2 == 0) {
            moveType = 'X';
        } else {
            moveType = 'O';
        }
    } while (gameActive);

    printf("Score: %d | %d\n", *fScore, *sScore);
    *gameState = 1;
}


/* ----------- xxx ----------- */


void inputCheck(int *in) {
    int inputVal
    , notInt = 1;
    do {
        if (scanf("%d", &inputVal) != 1 || (inputVal != 0 && inputVal != 1)) {
            printf("0 or 1 mf\n");
            // flushes input of scanf, resets it
            clearInputBuffer();
        } else {
            notInt = 0;
        }
    } while (notInt);

    *in = inputVal;
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void slctFPlayer(int inputVal, char *moveType, int *switchVal) {
    if (inputVal == 0) {
        *moveType = 'X';
        *switchVal = 0;
    } else {
        *moveType = 'O';
        *switchVal = 1;
    }
}

void makeBoard(char b[]) {
    printf("\n");
    printf(" %c | %c | %c\n", b[0], b[1], b[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", b[3], b[4], b[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", b[6], b[7], b[8]);
    printf("\n");
}

void moveInCheck(int *ptMoveInVal, char *boardVals) {
    int inputVal;
    int notInt = 1;
    do {
        if (scanf("%d", &inputVal) != 1 || (inputVal < 0 || inputVal > 9)) {
            printf("put correct value mf\n");
            clearInputBuffer();
        } else if (boardVals[inputVal] != ' ') {
            printf("Square already taken\n");
            clearInputBuffer();
        } else {
            notInt = 0;
        }
    } while (notInt);
    *ptMoveInVal = inputVal;
}

void makeAMove(char moveType, char *boardVals) {
    //prompt user
    int move;
    int *ptMoveInVal = &move;
    printf("Choose a space in the board (0-8 couting left to right)\n");
    moveInCheck(ptMoveInVal, boardVals);

    //make the move
    boardVals[*ptMoveInVal] = moveType;
}

int checkWin(char *b, char moveType, int *aScore) {
    // horizontal
    for (int h = 0; h < 9; h+=3) {
        if (b[h] == moveType) {
            if (b[h+1] == moveType) {
                if (b[h+2] == moveType) {
                    printf("%c wins!\n", moveType);
                    *aScore += 1;
                    return 1;
                }
            }
        }
    }
    // vertical
    for (int v = 0; v < 3; v++) {
        if (b[v] == moveType) {
            if (b[(v+3)] == moveType) {
                if (b[(v+6)] == moveType) {
                    printf("%c wins!\n", moveType);
                    *aScore += 1;
                    return 1;
                }
            }
        }
    }
    // diagonal
    // top left
    for (int d = 0; d < 8; d+=4) {
        if (b[d] == moveType) {
            if (b[(d+4)] == moveType) {
                if (b[(d+8)] == moveType) {
                    printf("%c wins!\n", moveType);
                    *aScore += 1;
                    return 1;
                }
            }
        }
    }
    // bottom left
    for (int d = 2; d < 7; d+=2) {
        if (b[d] == moveType) {
            if (b[(d+2)] == moveType) {
                if (b[(d+4)] == moveType) {
                    printf("%c wins!\n", moveType);
                    *aScore += 1;
                    return 1;
                }
            }
        }
    }
    return 0;
}