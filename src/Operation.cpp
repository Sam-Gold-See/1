#include "../include/Operation.h"

Operation::Operation()
{
}

Operation::~Operation()
{
}

void Operation::pushOperation(int row, int col, int value, bool isTrue)
{
    operationStack.push({row, col, value, isTrue});
}

operation Operation::popOperation()
{
    if (!operationStack.empty())
    {
        operation temp = operationStack.top();
        operationStack.pop();
        return temp;
    }
    else return operation{-1, -1, -1, false};
}
