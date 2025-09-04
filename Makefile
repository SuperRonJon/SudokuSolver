out/sudoku: out/box.o out/board.o out/sudokusolver.o out/inputparser.o
	g++ -O2 out/box.o out/board.o out/sudokusolver.o out/inputparser.o -o out/sudoku

out/sudokusolver.o: SudokuSolver.cpp
	g++ -c -O2 SudokuSolver.cpp -o out/sudokusolver.o

out/inputparser.o: InputParser.cpp
	g++ -c -O2 InputParser.cpp -o out/inputparser.o

out/board.o: Board.cpp
	g++ -c -O2 Board.cpp -o out/board.o

out/box.o: Box.cpp
	g++ -c -O2 Box.cpp -o out/box.o

out/debug: SudokuSolver.cpp InputParser.cpp Board.cpp Box.cpp
	g++ Box.cpp Board.cpp InputParser.cpp SudokuSolver.cpp -o out/debug -g

debug: out/debug

sudoku: out/sudoku

all: out/debug out/sudoku

clean:
	del out\*

clean-linux:
	rm out/*.o out/sudoku
