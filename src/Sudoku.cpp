#include "../include/Sudoku.h"
#include "../include/Utils.h"
#include "../include/Level.h"

Sudoku::Sudoku()
{
    initSudokuBoard();
    Utils::initUtils();
    generateSudoku();
}

Sudoku::~Sudoku()
{
}

void Sudoku::setSudokuBoard(Board sudokuBoard)
{
    this->sudokuBoard = Board(sudokuBoard);
}

void Sudoku::setSudokuAnswer(Board sudokuAnswer)
{
    this->sudokuAnswer = Board(sudokuAnswer);
}

Board Sudoku::getSudokuBoard()
{
    return this->sudokuBoard;
}

Board Sudoku::getSudokuAnswer()
{
    return this->sudokuAnswer;
}

void Sudoku::initSudokuBoard()
{
    sudokuBoard = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0));
    sudokuAnswer = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0));
    rowUsed.resize(BOARDSIZE);
    colUsed.resize(BOARDSIZE);
    blockUsed.resize(BOARDSIZE);
}

void Sudoku::initSudokuStatus()
{
    rowUsed.clear();
    colUsed.clear();
    blockUsed.clear();
}

void Sudoku::generateSudoku()
{
    std::vector<int> seq = Utils::getRandSequence();
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            sudokuBoard[3 + row][3 + col] = seq[row * 3 + col];
    Utils::boardChangeCopy(sudokuBoard, true, 3, 3);
    Utils::boardChangeCopy(sudokuBoard, false, 3, 0);
    Utils::boardChangeCopy(sudokuBoard, false, 3, 3);
    Utils::boardChangeCopy(sudokuBoard, false, 3, 6);
    sudokuAnswer = Board(sudokuBoard);
    int digCount = Level::digCount;
    while (digCount)
    {
        int x = Utils::getRand(5,4);
        int y = Utils::getRand(5,4);
        sudokuBoard[x][y] = 0;
        digCount--;
    }
    Utils::printBoard(sudokuBoard);
    Utils::printBoard(sudokuAnswer);
}

bool Sudoku::checkSudoku()
{
    initSudokuStatus();
    for (int row = 0; row < BOARDSIZE; row++)
        for (int col = 0; col < BOARDSIZE; col++)
            if (sudokuBoard[row][col] != 0)
            {
                int digit = sudokuBoard[row][col];
                if ((rowUsed[row] | colUsed[col] | blockUsed[row / 3 * 3 + col / 3]) & (1 << digit))
                    return false;
                updateSudokuStatus(row, col, digit);
            }
    return true;
}

void Sudoku::updateSudokuStatus(int row, int col, int digit)
{
    rowUsed[row] ^= (1 << digit);
    colUsed[col] ^= (1 << digit);
    blockUsed[row / 3 * 3 + col / 3] ^= (1 << digit);
}
