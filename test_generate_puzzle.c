#include "sudoku_board.h"
#include <stdlib.h>
#include <stdio.h>
#include "backtracking_core_logic.h"
#include "sudoku_board_actions.h"
#include "puzzle_generator.h"

int test_empty_board_generation(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);
    answer = generate_puzzle(board, 0);
    print_board(board);
    return answer;
}

int test_full_board_generation(int rows, int columns) {
    int answer;
    Board* board = malloc((sizeof(Board)));
    create_empty_board(board, rows, columns);
    answer = generate_puzzle(board, (rows * columns) * (rows * columns));
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

    printf("%s result: %d \n", "test_full_board_generation", test_full_board_generation(3,3));
    printf("%s result: %d \n", "test_empty_board_generation", test_empty_board_generation(3,3));
    printf("%s result: %d \n", "test_random_filled__board_generation", test_random_filled__board_generation(3,3));
    return 0;
}
