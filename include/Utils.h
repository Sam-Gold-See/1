#ifndef UTILS_H
#define UTILS_H

#include <vector>

typedef std::vector<std::vector<int>> Board; //用于表示数独棋盘的二维线性表

class Utils
{
public:
    static void initUtils(); //初始化Utils类
    static int getRand(int mid, int range); //生成一个指定范围的随机数
    static std::vector<int> getRandSequence(); //生成由1-9组成的随机序列
    static void printBoard(const Board& board); //打印棋盘类数据
    static void boardChangeCopy(Board& sudokuBoard, bool isRow, int srcX, int srcY); //数独棋盘行列偏移变化
    static void boardRowCopy(Board& sudokuBoard, int srcX, int srcY, int dstX, int dstY, int len); //数独棋盘行复制
    static void boardColCopy(Board& sudokuBoard, int srcX, int srcY, int dstX, int dstY, int len); //数独棋盘列复制
};

#endif // UTILS_H
