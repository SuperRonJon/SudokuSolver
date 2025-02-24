sudoku: box.o board.o sudokusolver.o inputparser.o
	g++ out/box.o out/board.o out/sudokusolver.o out/inputparser.o -o out/sudoku

sudokusolver.o: SudokuSolver.cpp
	g++ -c SudokuSolver.cpp -o out/sudokusolver.o

inputparser.o: InputParser.cpp
	g++ -c InputParser.cpp -o out/inputparser.o

board.o: Board.cpp
	g++ -c Board.cpp -o out/board.o

box.o: Box.cpp
	g++ -c Box.cpp -o out/box.o

clean:
	del out\*

clean-linux:
	rm out/*
