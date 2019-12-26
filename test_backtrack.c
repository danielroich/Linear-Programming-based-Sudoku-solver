#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "backtracking_core_logic.h"
#include "sudoku_board_actions.h"

int test_free_board_deterministic_backtrack(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);

    answer = back_track(board, 1);
    free_board(board, rows, columns);
    return answer;
}

int test_free_board_randomized_backtrack(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);
    print_board(board);
    answer = back_track(board, 0);
    print_board(board);
    free_board(board, rows, columns);
    return answer;
}

int main() {

    printf("%s result: %d \n", "test_free_board_randomized_backtrack", test_free_board_randomized_backtrack(3,3));
    return 0;
}