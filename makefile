CC = gcc
OBJS = main.o sudoku_board.o backtracking_core_logic.o sudoku_board_actions.o puzzle_generator.o 2d_array_utils.o parser.o backtrack_core.o file_utils.o LP.o moves.o stack_backtrack_logic.o stack.o 
EXEC = sudoku-console
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
main.o: main.c parser.h sudoku_board_actions.h
	$(CC) $(COMP_FLAGS) -c $*.c
sudoku_board.o: sudoku_board.c sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
file_utils.o: file_utils.c file_utils.h sudoku_board.h
	$(CC) $(COMP_FLAG) -c $*.c
2d_array_utils.o: 2d_array_utils.c 2d_array_utils.h optional_cell_values.h
	$(CC) $(COMP_FLAG) -c $*.c
backtracking_core_logic.o: backtracking_core_logic.c backtracking_core_logic.h sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c parser.h sudoku_board_actions.h moves.h
	$(CC) $(COMP_FLAG) -c $*.c
sudoku_board_actions.o: sudoku_board_actions.c sudoku_board_actions.h puzzle_generator.h 2d_array_utils.h backtracking_core_logic.h stack_backtrack_logic.h file_utils.h LP.h
	$(CC) $(COMP_FLAG) -c $*.c
puzzle_generator.o: puzzle_generator.c puzzle_generator.h 2d_array_utils.h sudoku_board.h backtracking_core_logic.h
	$(CC) $(COMP_FLAG) -c $*.c
backtrack_core.o: backtrack_core.c backtrack_core.h sudoku_board_actions.h sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
LP.o: LP.c LP.h sudoku_board.h backtrack_core.h gurobi_variable.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
moves.o: moves.c moves.h sudoku_board.h
	$(CC) $(COMP_FLAG) -c $*.c
stack_backtrack_logic.o: stack_backtrack_logic.c stack_backtrack_logic.h sudoku_board.h backtrack_core.h sudoku_board_actions.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
