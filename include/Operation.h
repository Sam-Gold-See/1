#ifndef OPERATION_H
#define OPERATION_H

#include <stack>

struct operation
{
    int row;
    int col;
    int value;
    bool isTrue;
};//使用结构体自定义operation记录、存储每次操作的数据

class Operation
{
private:
    std::stack<operation> operationStack;//关于操作记录，在底层使用栈结构来存储操作

public:
    void pushOperation(int row, int col, int value, bool isTrue);//进行一次操作前，将记录该操作落实前的该方块状态
    operation popOperation();//pop出上次操作改变前的一个数独棋盘状态并自动回溯至深层次
};

#endif //OPERATION_H
