# tictactoe

![Static Badge](https://img.shields.io/badge/version-1.0-blue)

Tic Tac Toe game implemented in C through the command line. Includes CUnit test cases for the game functions, including coverage test.

## How To Use

To clone and run this program, you'll need [Git](https://git-scm.com) and [CUnit](https://sourceforge.net/projects/cunit/files/CUnit/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/11acc/tictactoe

# To run game
$ gcc tictactoe.c -o ttt
$ .\ttt

# To run CUnit test cases
$ gcc ttt_without_main.c ttt_test.c -o ttt_test -lcunit
$ .\ttt

# To run coverage testing
$ gcc --coverage ttt_without_main.c ttt_test.c -o ttt_test -lcunit
$ gcov ttt_test-ttt_without_main
```

> **Note**
> We compile `ttt_without_main.c` for CUnit testing in order to not remove the `int main()` function from `tictactoe.c` due to function clashing. `ttt_without_main.c` includes all functions except `int main()` from `tictactoe.c`

## Testing and coverage

In the current test file, various test suites were designed to test the effectiveness of the tictactoe.c functions. Both expected successful and failure test cases were designed in order to fully validate the functions. In the end, test suites didn’t uncover any issues in the code that weren’t expected.

The test case coverage was surprisingly low, only executing 35% of the original files. This was surprising, but in retrospect, it made sense since part of the testing process was re-making functions in the test case file (ttt_test.c) due to their lack of testing capabilities. Analysing the gcov file, if we exclude lines that prompted the user for input or read/wrote files, only the functions modified for test cases remained as the ones which weren’t executed.

The test cases and coverage have served a good learning opportunity: to keep test cases and CUnit functionalities in mind when designing the various functionalities a program will use.

## Contributing/License

Fork it, modify it, push it, eat it, summon a duck god with it. Whatever resonable and day-to-day activity you prefer ( •ᴗ•)b
