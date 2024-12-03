#include "../include/Operation.h"

void Operation::pushOperation(int row, int col, int value, bool isTrue)
{
    operationStack.push({row, col, value, isTrue}); //将传入数据封装成operation结构体并且压入栈中
}

operation Operation::popOperation()
{
    if (!operationStack.empty()) //检测是否栈空，以免造成栈越位
    {
        operation temp = operationStack.top();//获取当前栈内顶部的operation对象
        operationStack.pop();//将当前栈顶部的operation对象弹出，便于在下次使用的时候返回更早之前的数独棋盘状态
        return temp;//将获取到的operation对象返回到主程序中
    }
    else return operation{-1, -1, -1, false}; //如果栈空，则返回自定义的错误operation数据，让主程序根据此数据判断是否成功获取上次操作前的数独棋盘状态
}
