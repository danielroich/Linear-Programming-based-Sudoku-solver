#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>
#include "backtracking_core_logic.h"
#include "sudoku_board_actions.h"
#include "puzzle_generator.h"

int test_exact_board_generation(int rows, int columns, int fixed) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);
    answer = generate_puzzle(board, fixed);
    print_board(board);
    return answer;
}

int test_random_filled__board_generation(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);
    answer = generate_puzzle(board, rand() % ((rows * columns) * (rows * columns)));
    print_board(board);
    return answer;
}

int main() {

    printf("%s result: %d \n", "test_exact_board_generation", test_exact_board_generation(3,3, 5));
    return 0;
}
