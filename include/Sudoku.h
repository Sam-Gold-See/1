#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

typedef std::vector<std::vector<int>> Board; //用于表示数独棋盘的二维线性表

class Sudoku
{
private:
    Board sudokuBoard; //用于存储数独游戏的当前布局
    Board sudokuQuestion; //用于存储数独游戏的问题布局
    Board sudokuAnswer; //用于存储数独游戏生成过程中某个存在解
    std::vector<int> rowUsed; //记录行的存入数据
    std::vector<int> colUsed; //记录列的存入数据
    std::vector<int> blockUsed; //记录宫的存入数据
    std::vector<std::pair<int, int>> emptySite; //用于DFS搜索时候存储发现的空缺位置
    bool DFSFlag;

public:
    Sudoku(); //Sudoku类的默认构造函数
    ~Sudoku(); //Sudoku类的析构函数

    constexpr static int BOARDSIZE = 9; //常量表达式，表示数独棋盘的大小
    constexpr static int NUMFLAG = 0b1111111110; //数独行列宫已满标志（位）

    void setSudokuBoard(Board board); //设置数独游戏的棋盘布局
    Board getSudokuBoard(); //获取数独游戏的当前棋盘布局
    Board getSudokuAnswer(); //获取数独游戏的答案（DFS结果/某个存在解）
    Board getSudokuQuestion(); //获取数独游戏的初始棋盘布局

    void initSudokuBoard(); //初始化数独游戏
    void initSudokuStatus(); //初始化数独的查询状态
    void generateSudoku(); //生成数独游戏棋盘
    bool checkSudoku(); //检查当前数独盘是否符合数独游戏规则
    void updateSudokuStatus(int row, int col, int digit); //更新数独的查询状态
    bool checkEmptySite();//检查数独棋盘当前布局是否有空，并且将空位记录在emptySite中

    int getSudokuNumber(int row, int col); //获取数独棋盘的数字
    bool setSudokuNumber(int value, int row, int col); //把数字填入数独棋盘，并检查是否违反数独规则
    void deleteSudokuNumber(int row, int col); //把填入的数字删除

    Board DFS(int pos); //DFS函数搜索答案
};

#endif // SUDOKU_H
