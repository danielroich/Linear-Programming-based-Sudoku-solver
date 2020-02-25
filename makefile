CC = gcc
OBJS = main.o backtracking_core_logic.o sudoku_board.o sudoku_board_actions.o puzzle_generator.o 2d_array_utils.o parser.o backtrack_core.o files_utils.o LP.o moves_list.0 stack_backtrack_logic.o stack.o
EXEC = sudoku
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
main.o: main.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c
files_utils.o: files_utils.c sudoku_board.h backtrack_core.h
	$(CC) $(COMP_FLAG) -c $*.c
2d_array_utils.o: 2d_array_utils.c
	$(CC) $(COMP_FLAG) -c $*.c
backtracking_core_logic.o: backtracking_core_logic.c sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c sudoku_board_actions.h moves_list.h
	$(CC) $(COMP_FLAG) -c $*.c
sudoku_board_actions.o: sudoku_board_actions.c puzzle_generator.h 2d_array_utils.h backtracking_core_logic.h stack_backtrack_logic.h files_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
sudoku_board.o: sudoku_board.c sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
puzzle_generator.o: puzzle_generator.c 2d_array_utils.h sudoku_board.h backtracking_core_logic.h
	$(CC) $(COMP_FLAG) -c $*.c
backtrack_core.o: backtrack_core.c sudoku_board_actions.h sudoku_board.h 2d_array_utils.h
	$(CC) $(COMP_FLAG) -c $*.c
LP.o: LP.c sudoku_board.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
moves_list.o: moves_list.c sudoku_board.h
	$(CC) $(COMP_FLAG) -c $*.c
stack_backtrack_logic.o: stack_backtrack_logic.c sudoku_board.h backtrack_core.h sudoku_board_actions.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
