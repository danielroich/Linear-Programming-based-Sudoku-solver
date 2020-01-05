CC = gcc
OBJS = main.o backtracking_core_logic.o sudoku_board.o sudoku_board_actions.o puzzle_generator.o 2d_array_utils.o parser.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -lm -o $@
main.o: main.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c
2d_array_utils.o: 2d_array_utils.c
	$(CC) $(COMP_FLAG) -c $*.c
backtracking_core_logic.o: backtracking_core_logic.c sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c sudoku_board_actions.h
	$(CC) $(COMP_FLAG) -c $*.c
sudoku_board_actions.o: sudoku_board_actions.c puzzle_generator.h 2d_array_utils.h backtracking_core_logic.h
	$(CC) $(COMP_FLAG) -c $*.c
sudoku_board.o: sudoku_board.c sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
puzzle_generator.o: puzzle_generator.c 2d_array_utils.h sudoku_board.h backtracking_core_logic.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
