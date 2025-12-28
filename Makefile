build/sudoku: build/box.o build/board.o build/sudokusolver.o build/argumentparser.o
	g++ -Wall -Wextra -O2 build/box.o build/board.o build/sudokusolver.o build/argumentparser.o -o build/sudoku

build/sudokusolver.o: src/SudokuSolver.cpp
	g++ -Wall -Wextra -c -O2 src/SudokuSolver.cpp -o build/sudokusolver.o

build/argumentparser.o: src/ArgumentParser.cpp
	g++ -Wall -Wextra -c -O2 src/ArgumentParser.cpp -o build/argumentparser.o

build/board.o: src/Board.cpp
	g++ -Wall -Wextra -c -O2 src/Board.cpp -o build/board.o

build/box.o: src/Box.cpp
	g++ -Wall -Wextra -c -O2 src/Box.cpp -o build/box.o

build/debug: src/SudokuSolver.cpp src/ArgumentParser.cpp src/Board.cpp src/Box.cpp
	g++ -Wall -Wextra -Wpedantic src/Box.cpp src/Board.cpp src/ArgumentParser.cpp src/SudokuSolver.cpp -o build/debug -g

debug: build/debug

sudoku: build/sudoku

all: build/debug build/sudoku

clean-windows:
	del build\*

clean:
	rm -f build/*.o build/sudoku build/debug
