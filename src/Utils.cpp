#include "../include/Utils.h"
#include "../include/Sudoku.h"

#include <iostream>
#include <ctime>
#include <random>

void Utils::initUtils()
{
    srand(time(nullptr));
}

int Utils::getRand(int mid, int range)
{
    return rand() % (2 * range + 1) + mid - range;
}

std::vector<int> Utils::getRandSequence()
{
    std::vector<int> seq;
    int numUsed = 0;
    while (seq.size() != 9)
    {
        int num = rand() % 9 + 1;
        if ((1 << num) & numUsed)
            continue;
        else
        {
            seq.push_back(num);
            numUsed ^= (1 << num);
        }
    }
    return seq;
}

void Utils::printBoard(const Board& board)
{
    for (int row = 0; row < Sudoku::BOARDSIZE; row++)
    {
        for (int col = 0; col < Sudoku::BOARDSIZE; col++)
            std::cout << board[row][col] << " ";
        std::cout << std::endl;
    }
}

void Utils::boardChangeCopy(Board& sudokuBoard, bool isRow, int srcX, int srcY)
{
    std::vector<int> dstX;
    std::vector<int> dstY;
    if (isRow)
        dstY = {srcY - 3, srcY + 3}, dstX = {srcX};
    else
        dstY = {srcY}, dstX = {srcX - 3, srcX + 3};
    int posFlag1 = 1;
    int posFlag2 = 2; // 位置偏移量
    if (isRow)
        for (int row = 0; row < 3; row++)
        {
            boardRowCopy(sudokuBoard, srcX + row, srcY, dstX[0] + (row + posFlag1) % 3, dstY[0], 3);
            boardRowCopy(sudokuBoard, srcX + row, srcY, dstX[0] + (row + posFlag2) % 3, dstY[1], 3);
        }
    else
        for (int col = 0; col < 3; col++)
        {
            boardColCopy(sudokuBoard, srcX, srcY + col, dstX[0], dstY[0] + (col + posFlag1) % 3, 3);
            boardColCopy(sudokuBoard, srcX, srcY + col, dstX[1], dstY[0] + (col + posFlag2) % 3, 3);
        }
}

void Utils::boardRowCopy(Board& sudokuBoard, int srcX, int srcY, int dstX, int dstY, int len)
{
    for (int col = 0; col < len; col++)
        sudokuBoard[dstX][dstY + col] = sudokuBoard[srcX][srcY + col];
}

void Utils::boardColCopy(Board& sudokuBoard, int srcX, int srcY, int dstX, int dstY, int len)
{
    for (int row = 0; row < len; row++)
        sudokuBoard[dstX + row][dstY] = sudokuBoard[srcX + row][srcY];
}
