#include "../include/Sudoku.h"
#include "../include/Utils.h"
#include "../include/Level.h"

Sudoku::Sudoku()
{
    initSudokuBoard();
    generateSudoku();
}

Sudoku::~Sudoku()
= default;

void Sudoku::setSudokuBoard(Board board)
{
    this->sudokuBoard = Board(board);
}

Board Sudoku::getSudokuBoard()
{
    return this->sudokuBoard;
}

Board Sudoku::getSudokuAnswer()
{
    return this->sudokuAnswer;
}

Board Sudoku::getSudokuQuestion()
{
    return this->sudokuQuestion;
}

void Sudoku::initSudokuBoard()
{
    sudokuBoard = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0));
    sudokuAnswer = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0));
    sudokuQuestion = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0));
    rowUsed.resize(BOARDSIZE);
    colUsed.resize(BOARDSIZE);
    blockUsed.resize(BOARDSIZE);
    emptySite.resize(0);
}

void Sudoku::initSudokuStatus()
{
    for (int i = 0; i < BOARDSIZE; i++)
    {
        rowUsed[i] = 0;
        colUsed[i] = 0;
        blockUsed[i] = 0;
    }
    emptySite.resize(0);
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
        int x = Utils::getRand(4, 4);
        int y = Utils::getRand(4, 4);
        sudokuBoard[x][y] = 0;
        digCount--;
    }
    sudokuQuestion = Board(sudokuBoard);
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

Board Sudoku::solveSudoku()
{
    initSudokuStatus();
    for (int row = 0; row < BOARDSIZE; row++)
    {
        for (int col = 0; col < BOARDSIZE; col++)
        {
            if (sudokuBoard[row][col] == 0)
                emptySite.emplace_back(row, col);
            else
                updateSudokuStatus(row, col, sudokuBoard[row][col]);
        }
    }
    return DFS(0);
}

int Sudoku::getSudokuNumber(int row, int col)
{
    return sudokuBoard[row][col];
}

bool Sudoku::setSudokuNumber(int value, int row, int col)
{
    sudokuBoard[row][col] = value;
    return checkSudoku();
}

void Sudoku::deleteSudokuNumber(int row, int col)
{
    if (sudokuQuestion[row][col] == 0)
        sudokuBoard[row][col] = 0;
}

Board Sudoku::DFS(int pos)
{
    if (pos == emptySite.size())
        return sudokuBoard;
    int row = emptySite[pos].first;
    int col = emptySite[pos].second;
    for (int i = 1; i <= BOARDSIZE; i++)
    {
        int digit = sudokuBoard[row][col];
        if ((rowUsed[row] | colUsed[col] | blockUsed[row / 3 * 3 + col / 3]) & (1 << digit))
        {
            sudokuBoard[row][col] = digit;
            updateSudokuStatus(row, col, digit);
            DFS(pos + 1);
            updateSudokuStatus(row, col, digit);
            sudokuBoard[row][col] = 0;
        }
    }
    return sudokuAnswer;
}
