
//
// file for cunit testing purposes
// 11acc / alejandro gutierrez acosta

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to hold the game state and score
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

/* ----------- xxx ----------- */

GameState initialiseGame() {
    // load previous game state if it exists
    // printf("loading game...\n");
    GameState gameState;
    int stateGame = loadGame(&gameState);

    if (stateGame) {
        // sucess return loaded game
        return gameState;
    }

    // if file does not exist, is empty, or failed to load then initialize a new game
    // printf("initializing new game\n");
    GameState newGameState = {
        .board = "         ",
        .p1Score = 0,
        .p2Score = 0,
        .currPlayer = 0
    };
    return newGameState;
}

void updateNSave(GameState* gameState, int xScore, int oScore, int counter, int win, char b[]) {
    // update gameState before saving
    gameState->p1Score = xScore;
    gameState->p2Score = oScore;
    gameState->currPlayer = counter;
    // to avoid text problems save empty spaces as 'e'
    for(int i = 0; i < 9; i++) {
        gameState->board[i] = b[i] == ' ' ? 'e' : b[i];
    }

    // writing...
    FILE *file = fopen("ttt_save_data.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "error opening file for writing\n");
        return;
    }
    // write the score and current player
    fprintf(file, "%d %d %d\n", gameState->p1Score, gameState->p2Score, gameState->currPlayer);

    // if game finished, don't save the board
    if (win) {
        // printf("saving game as empty because of win\n");
        strcpy(gameState->board, "         ");  // set elems to spaces for an empty board
        fprintf(file, "11acc_dont_read_board");
    } else {
        for (int i = 0; i < 9; i++) {
            fprintf(file, "%c ", gameState->board[i]);
        }
    }

    fclose(file);
}

int loadGame(GameState* gameState) {
    // 0 for empty/fail, 1 for sucess
    FILE *file = fopen("ttt_save_data.txt", "r");

    if (file != NULL) {
        // check if the file is empty
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file); // rewind to top of file

        if (fileSize == 0) {
            // printf("save file empty\n");
            fclose(file);
            return 0;
        } else {
            // we have smth, lets load it
            // read the score and current player
            fscanf(file, "%d %d %d\n", &gameState->p1Score, &gameState->p2Score, &gameState->currPlayer);

            // read the board state
            // first check if board should be empty
            char checkEmpty[22];
            fscanf(file, "%21s", checkEmpty);

            if (strcmp(checkEmpty, "11acc_dont_read_board") == 0) {
                // board should be empty
                printf("loading board as empty\n");
                strcpy(gameState->board, "         ");
            } else {
                fseek(file, -strlen(checkEmpty), SEEK_CUR); // go back to start reading the board
                for (int i = 0; i < 9; i++) {
                    char c;
                    fscanf(file, "%c", &c);
                    gameState->board[i] = c == 'e' ? ' ' : c;  // replace 'e' with space
                }
                gameState->board[9] = '\0'; // Null-terminate the string
            }

            // printf("loaded successfully\n");
            fclose(file);
            return 1;
        }
    } else {
        // printf("error opening the save file\n");
        return 0;
    }
}

/* ----------- xxx ----------- */

char checkPlayerOrder(int c) {
    char player = ' ';
    if (c % 2 == 0) {
        player = 'X';
    } else {
        player = 'O';
    }
    return player;
}

void displayGrid(char b[]) {
    printf("\n");
    printf(" %c | %c | %c\n", b[0], b[1], b[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", b[3], b[4], b[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c\n", b[6], b[7], b[8]);
    printf("\n");
}

void isDraw(int *gC, char b[]) {
    if (strchr(b, ' ') == NULL) {
        *gC = 0; // false, game stops
    }
}

void isValidMove(int *move, char b[]) {
    int inputVal
        , notValid=1;
    do {
        // check if input is a number and 0-8 inclusive
        if (scanf("%d", &inputVal) != 1 || (inputVal < 0 || inputVal > 8)) {
            // printf("Please input valid number\n");
            clearInputBuffer();
        // check if move is on tile already occupied
        } else if (b[inputVal] != ' ') {
            // printf("Position already taken\n");
            clearInputBuffer();
        } else {
            notValid = 0;
        }
    } while (notValid);
    *move = inputVal;
}
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int checkWin(char b[], char p) {
    // horizontal
    for (int h = 0; h < 9; h+=3) {
        if (b[h] == p) {
            if (b[h+1] == p) {
                if (b[h+2] == p) {
                    // printf("Player %c wins!\n", p);
                    return 1;
                }
            }
        }
    }
    // vertical
    for (int v = 0; v < 3; v++) {
        if (b[v] == p) {
            if (b[(v+3)] == p) {
                if (b[(v+6)] == p) {
                    // printf("Player %c wins!\n", p);
                    return 1;
                }
            }
        }
    }
    // diagonal
    // top left
    if (b[0] == p) {
        if (b[(4)] == p) {
            if (b[(8)] == p) {
                // printf("Player %c wins!\n", p);
                return 1;
            }
        }
    }
    // bottom left
    if (b[2] == p) {
        if (b[(4)] == p) {
            if (b[6] == p) {
                // printf("Player %c wins!\n", p);
                return 1;
            }
        }
    }

    return 0;
}