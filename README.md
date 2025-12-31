# Sudoku Solver

CLI Sudoku puzzle solver with a custom generic command line argument parser.

```
$ sudoku -b x56xxx27872xx361xx8xxxxx46x5xxx47xxx4x9xxx7x5xxx65xxx4x35xxxxx7xx718xx32918xxx54x

x 5 6 | x x x | 2 7 8
7 2 x | x 3 6 | 1 x x
8 x x | x x x | 4 6 x
------+-------+------
5 x x | x 4 7 | x x x
4 x 9 | x x x | 7 x 5
x x x | 6 5 x | x x 4
------+-------+------
x 3 5 | x x x | x x 7
x x 7 | 1 8 x | x 3 2
9 1 8 | x x x | 5 4 x
Solved!
3 5 6 | 4 9 1 | 2 7 8
7 2 4 | 8 3 6 | 1 5 9
8 9 1 | 5 7 2 | 4 6 3
------+-------+------
5 8 3 | 2 4 7 | 6 9 1
4 6 9 | 3 1 8 | 7 2 5
1 7 2 | 6 5 9 | 3 8 4
------+-------+------
2 3 5 | 9 6 4 | 8 1 7
6 4 7 | 1 8 5 | 9 3 2
9 1 8 | 7 2 3 | 5 4 6
```

## Options

```
$ sudoku --help
Sudoku Solver

Usage:
       sudoku [OPTIONS...] <board-string>|<file-path>
Options:
  --help, -h                   Prints help menu.
  --version, -v                Prints version number.
  --example, -e                Prints an example valid board string.
  --count, -c                  Prints the total number of individual box checks required to solve.
  --file, -f                   Reads boards line by line from an input file path rather than a single string.
  --print-solved, -p           Prints only the solved board, not the starting board.
  --required-checks, -r VAL    If counting and from a file input, prints all boards in file above this number of checks.
  --borders, -b                Print board with border lines.
```

The program accepts a string representation of a board, with numbers and "empty characters" to represent empty boxes. Valid empty characters are 'x', 'X', '0', 'O', 'o', or '.'. String must be exactly 81 characters long (representing a full 9x9 game board).

With the -f flag or --file option, instead of a single baord string the program will instead accept a filepath to a text file containing a list of board strings, one per line in the file.

## Installation

Pre-built binaries for Linux & Windows x86_64 are available from the [releases page](https://github.com/SuperRonJon/SudokuSolver/releases/latest)

Otherwise it can be built from source using make with g++.