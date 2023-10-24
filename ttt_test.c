
//
// program that runs test cases on tictactoe.c
// 11acc / alejandro gutierrez acosta

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
// #include "C:/CUnit-2.1-2/CUnit/Headers/Basic.h" // for CLion
#include "tictactoe.h"

// declaring functions
int isValidMove_Test(int in, char b[]);
int isDraw_Test(char b[]);
int loadGame_Test(char b_str[]);

// Initialize and clean up test suite
int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

// test case functions
void win_testing() {
    // horizontal
    CU_ASSERT(checkWin("XXX      ", 'X') == 1);
    // vertical
    CU_ASSERT(checkWin("O  O  O  ", 'O') == 1);
    // diagonal
    CU_ASSERT(checkWin("X   X   X", 'X') == 1);
    // false test cases
    CU_ASSERT(checkWin("X   X   X", 'O') == 1);
    CU_ASSERT(checkWin("OOOX   X", 'X') == 1);
}

void valid_move_testing() {
    // using modified function here to avoid scanf
    // 0-8 verification
    CU_ASSERT(isValidMove_Test(0, "         ") == 1);
    CU_ASSERT(isValidMove_Test(9, "X   X    ") == 0);
    CU_ASSERT(isValidMove_Test(8, "X   XO  O") == 0);
    // false test cases
    CU_ASSERT(isValidMove_Test(0, "X   X    ") == 1);
    CU_ASSERT(isValidMove_Test(2, "OO X   X") == 0);
}

void isdraw_testing() {
    // using modified function here due to function
    // configuration with pointers
    CU_ASSERT(isDraw_Test("         ") == 0);
    CU_ASSERT(isDraw_Test("XOXOXOXOX") == 1);
    // false test cases
    CU_ASSERT(isDraw_Test("         ") == 1);
    CU_ASSERT(isDraw_Test("OXOXOXOXO") == 0);
}

void init_game_testing() {
    // basic struct variable checks
    GameState gameState = {
        .board = "         ",
        .p1Score = 0,
        .p2Score = 0,
        .currPlayer = 0
    };
    CU_ASSERT_EQUAL(gameState.p1Score, 0);
    CU_ASSERT_EQUAL(gameState.p2Score, 0);
    CU_ASSERT_STRING_EQUAL(gameState.board, "         ");
    // verify save state loading
    CU_ASSERT(loadGame(&gameState) == 1);
    // using modified function to check parts of the code
    // that require file reading
    CU_ASSERT(loadGame_Test("XO XO OXO") == 1);
    CU_ASSERT(loadGame_Test("") == 0);

    // false test cases
    CU_ASSERT(loadGame_Test("XO XO OXY") == 1);
    CU_ASSERT(loadGame_Test("XO XO ") == 1);
}

int main() {
    // initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    
    // win_testing  valid_move_testing  isdraw_testing  init_game_testing

    // win_testing
    CU_pSuite suite_win = CU_add_suite("win_testing", init_suite, clean_suite);
    if (NULL == suite_win) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(suite_win, "win_testing", win_testing))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // valid_move_testing
    CU_pSuite suite_move = CU_add_suite("valid_move_testing", init_suite, clean_suite);
    if (NULL == suite_move) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(suite_move, "init_game_testing", init_game_testing))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // isdraw_testing
    CU_pSuite suite_draw = CU_add_suite("isdraw_testing", init_suite, clean_suite);
    if (NULL == suite_draw) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(suite_draw, "init_game_testing", init_game_testing))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    // init_game_testing
    CU_pSuite suite_init = CU_add_suite("init_game_testing", init_suite, clean_suite);
    if (NULL == suite_init) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(suite_init, "init_game_testing", init_game_testing))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // run the tests
    CU_basic_run_tests();

    // display test results
    // CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_cleanup_registry();
    return CU_get_error();
}



/* ----------- xxx ----------- */

int isValidMove_Test(int in, char b[]) {
    // 0 false, 1 true
    if (in < 0 || in > 8) {
        // if out of bounds
        return 0;
    } else if (b[in] != ' ') {
        // if square already taken
        return 0;
    }
    return 1;
}
int isDraw_Test(char b[]) {
    // 0 false, 1 true
    if (strchr(b, ' ') == NULL) {
        // no empty squares, therefore a draw
        return 0;
    }
    return 1;
}
int loadGame_Test(char b_str[]) {
    // if board is empty or less than 9 char long, fail
    if (b_str[0] == '\0' || strlen(b_str) != 9) {
        return 0;
    }
    // if it contains something other than ' ', 'X' or 'O', fail
    for (int i = 0; i < 9; i++) {
        if (b_str[i] != ' ' && b_str[i] != 'X' && b_str[i] != 'O') {
            return 0;
        }
    }
    return 1;
}