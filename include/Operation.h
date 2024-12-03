#ifndef OPERATION_H
#define OPERATION_H

#include <stack>

struct operation
{
    int row;
    int col;
    int value;
    bool isTrue;
};

class Operation
{
private:
    std::stack<operation> operationStack;

public:
    Operation();
    ~Operation();

    void pushOperation(int row, int col, int value, bool isTrue);//
    operation popOperation();//
};

#endif //OPERATION_H
