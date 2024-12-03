#include "../include/Utils.h"
#include "../include/Sudoku.h"

#include <iostream>
#include <ctime>
#include <random>

void Utils::initUtils()
{
    srand(time(nullptr)); //设置随机数种子
}

int Utils::getRand(int mid, int range)
{
    return rand() % (2 * range + 1) + mid - range; //根据传入的mid数，生成[mid-range,mid+range]范围的随机数
}

std::vector<int> Utils::getRandSequence()
{
    std::vector<int> seq; //初始化该随机数序列
    int numUsed = 0; //作为位运算标志记录当前随机数序列的数字使用情况
    while (seq.size() != 9) //设置break条件为随机数包含1-9所有数字1
    {
        int num = rand() % 9 + 1; //num取值范围为1-9
        if (!(1 << num & numUsed))//将数字1左移num位置，同时和位运算标志进行&运算，判断num是否出现过，最后进行取反操作，使得没出现过的num进入if中
        {
            seq.push_back(num);//将num压入随机数序列队尾
            numUsed ^= (1 << num);//更新位运算标志
        }
    }
    return seq;//传回随机数序列
}

void Utils::printBoard(const Board& board)//对于传入的数独棋盘，在控制台打印输出（用于调试）
{
    for (int row = 0; row < Sudoku::BOARDSIZE; row++)//遍历行
    {
        for (int col = 0; col < Sudoku::BOARDSIZE; col++)//遍历列
            std::cout << board[row][col] << " ";//输出
        std::cout << std::endl;//换行
    }
}

void Utils::boardChangeCopy(Board& sudokuBoard, bool isRow, int srcX, int srcY)
{
    std::vector<int> dstX;//初始化目标行列的数组，根据是否行变化，相对的目标行、列的个数不一
    std::vector<int> dstY;
    if (isRow)//矩阵行变化，要设置两个目标列
        dstY = {srcY - 3, srcY + 3}, dstX = {srcX};
    else//矩阵列变化，要设置两个目标行
        dstY = {srcY}, dstX = {srcX - 3, srcX + 3};
    int posFlag1 = 1; // 位置偏移量1
    int posFlag2 = 2; // 位置偏移量2
    if (isRow)//行变化操作
        for (int row = 0; row < 3; row++)//复制的矩阵对象行遍历
        {
            boardRowCopy(sudokuBoard, srcX + row, srcY, dstX[0] + (row + posFlag1) % 3, dstY[0], 3);//偏移一次的矩阵行变化，使用取余操作使得操作不会越界/超出预想范围
            boardRowCopy(sudokuBoard, srcX + row, srcY, dstX[0] + (row + posFlag2) % 3, dstY[1], 3);//偏移两次的矩阵行变化，使用取余操作使得操作不会越界/超出预想范围
        }
    else//列变化操作
        for (int col = 0; col < 3; col++)//复制的矩阵对象列遍历
        {
            boardColCopy(sudokuBoard, srcX, srcY + col, dstX[0], dstY[0] + (col + posFlag1) % 3, 3);//偏移一次的矩阵列变化，使用取余操作使得操作不会越界/超出预想范围
            boardColCopy(sudokuBoard, srcX, srcY + col, dstX[1], dstY[0] + (col + posFlag2) % 3, 3);//偏移两次的矩阵列变化，使用取余操作使得操作不会越界/超出预想范围
        }
}

void Utils::boardRowCopy(Board& sudokuBoard, int srcX, int srcY, int dstX, int dstY, int len)//矩阵行变化复制
{
    for (int col = 0; col < len; col++)//遍历复制目标行和复制位置行的列，依次赋值
        sudokuBoard[dstX][dstY + col] = sudokuBoard[srcX][srcY + col];
}

void Utils::boardColCopy(Board& sudokuBoard, int srcX, int srcY, int dstX, int dstY, int len)//矩阵列变化复制
{
    for (int row = 0; row < len; row++)//遍历复制目标列和复制位置列的行，依次赋值
        sudokuBoard[dstX + row][dstY] = sudokuBoard[srcX + row][srcY];
}
