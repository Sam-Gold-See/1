#include "../include/Operation.h"

Operation::Operation()
{
}

Operation::~Operation()
{
}

void Operation::pushOperation(int row, int col, int value)
{
    operationStack.push({row, col, value});
}

operation Operation::popOperation()
{
    operation temp = operationStack.top();
    operationStack.pop();
    return temp;
}
