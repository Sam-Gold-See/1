#include "../include/Sudoku.h"
#include "../include/Utils.h"
#include "../include/Level.h"

Sudoku::Sudoku() //Sudoku构造函数
{
    initSudokuBoard(); //初始化Sudoku类对象的属性值
    generateSudoku(); //生成Sudoku棋盘
}

Sudoku::~Sudoku() //析构函数
= default;

void Sudoku::setSudokuBoard(Board board) //设置数独游戏的棋盘布局
{
    this->sudokuBoard = Board(board); //传入Board二位线性表设置数独游戏的当前布局
}

Board Sudoku::getSudokuBoard() //获取数独游戏的当前棋盘布局
{
    return this->sudokuBoard; //获得数独游戏当前的布局
}

Board Sudoku::getSudokuAnswer() //获取数独游戏的答案（DFS结果/某个存在解）
{
    if (checkEmptySite()) //如果存在空缺，则使用DFS搜索生成答案
    {
        sudokuBoard = DFS(0);
        if (DFSFlag)
            return sudokuBoard;
    }
    return this->sudokuAnswer; //获得数独游戏生成过程中获得的某个解
}

Board Sudoku::getSudokuQuestion() //获取数独游戏的初始棋盘布局
{
    return this->sudokuQuestion; //获得数独游戏生成时初始的挖空生成的问题布局
}

void Sudoku::initSudokuBoard() //初始化数独游戏内的各类属性值
{
    sudokuBoard = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0)); //给数独当前布局初始化大小
    sudokuAnswer = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0)); //给数独答案布局初始化大小
    sudokuQuestion = Board(BOARDSIZE, std::vector<int>(BOARDSIZE, 0)); //给数独问题布局初始化大小
    rowUsed.resize(BOARDSIZE); //初始化行查询的数组大小
    colUsed.resize(BOARDSIZE); //初始化列查询的数组大小
    blockUsed.resize(BOARDSIZE); //初始化宫查询的数组大小
    emptySite.resize(0); //初始化DFS查询的空区域数组大小
}

void Sudoku::initSudokuStatus() //初始化数独游戏的查询状态
{
    for (int i = 0; i < BOARDSIZE; i++) //初始化赋值行列宫查询的初始值
    {
        rowUsed[i] = 0;
        colUsed[i] = 0;
        blockUsed[i] = 0;
    }
    emptySite.resize(0); //重置DFS的查询状态
}

void Sudoku::generateSudoku() //生成数独棋盘答案版、问题版、当前布局版
{
    std::vector<int> seq = Utils::getRandSequence(); //获取Utils类中生成的随机数序列
    for (int row = 0; row < 3; row++) //将随机生成的随机数序列填入数独盘的中心3X3
        for (int col = 0; col < 3; col++)
            sudokuBoard[3 + row][3 + col] = seq[row * 3 + col];
    Utils::boardChangeCopy(sudokuBoard, true, 3, 3); //将中心3X3矩阵通过矩阵偏移行变化，生成左中、右中矩阵
    Utils::boardChangeCopy(sudokuBoard, false, 3, 0); //将左中矩阵通过矩阵偏移列变化，生成左上、左下矩阵
    Utils::boardChangeCopy(sudokuBoard, false, 3, 3); //将中心X3矩阵通过矩阵偏移列变化，生成中上、中下矩阵
    Utils::boardChangeCopy(sudokuBoard, false, 3, 6); //将右中矩阵通过矩阵偏移列变化，生成右上、右下矩阵
    sudokuAnswer = Board(sudokuBoard); //将此时的数独当前布局深拷贝到数独答案布局上
    int digCount = Level::digCount; //获取Level类中设置的digCount

    while (digCount) //当digCount非0的时候持续运行
    {
        int row = Utils::getRand(4, 4); //获取0-8之内的随机数充当选中行
        int col = Utils::getRand(4, 4); //获取0-9之内的随机数充当选中列
        if (sudokuBoard[row][col] == 0) //如果当前空格为空，即已经被挖空了，则跳过
            continue;
        sudokuBoard[row][col] = 0; //设置数独当前布局当前行列值为0
        digCount--; //若非空则可以挖空，挖空数--
    }
    sudokuQuestion = Board(sudokuBoard); //将挖空后的数独棋盘布局深拷贝到数独问题布局上
}

bool Sudoku::checkSudoku() //检查当前的数独棋盘是否符合数独游戏规则
{
    initSudokuStatus(); // 初始化数独的查询状态
    for (int row = 0; row < BOARDSIZE; row++) //遍历数独当前布局的每个值
        for (int col = 0; col < BOARDSIZE; col++)
            if (sudokuBoard[row][col] != 0) //如果当前行列有值
            {
                int digit = sudokuBoard[row][col];
                if ((rowUsed[row] | colUsed[col] | blockUsed[row / 3 * 3 + col / 3]) & (1 << digit))
                    //先使用|运算获取当前行列宫内的所有存在数字，然后与当前位置的数值进行&运算，若有重复数字，则返回值非0，即违规
                    return false;
                updateSudokuStatus(row, col, digit); //更新当前位置的数值到查询状态中，进行后续查询
            }
    return true; //遍历一遍无错误跳出则证明数独棋盘当前布局无不符合规则部分
}

void Sudoku::updateSudokuStatus(int row, int col, int digit) //更新数独的查询状态
{
    rowUsed[row] ^= (1 << digit); //更新数独行查询状态
    colUsed[col] ^= (1 << digit); //更新数独列查询状态
    blockUsed[row / 3 * 3 + col / 3] ^= (1 << digit); //更新数独宫查询状态
}

bool Sudoku::checkEmptySite() //检查数独棋盘当前布局是否有空，并且将空位记录在emptySite中
{
    initSudokuStatus(); //初始化数独查询状态
    for (int row = 0; row < BOARDSIZE; row++) //遍历数独棋盘
        for (int col = 0; col < BOARDSIZE; col++)
        {
            if (sudokuBoard[row][col] == 0) //判断该位置数独是否为0
                emptySite.emplace_back(row, col); //非0则记录该位置的行列值
            else
                updateSudokuStatus(row, col, sudokuBoard[row][col]); //是0则更新查询状态，便于DFS搜索过程中使用
        }
    if (emptySite.size() == 0) //如果为空，返回true，用于commit按钮的判断、和是否进行DFS查询的判断
        return true;
    return false;
}

int Sudoku::getSudokuNumber(int row, int col) //用于获取数独棋盘当前行列值的数值
{
    return sudokuBoard[row][col];
}

bool Sudoku::setSudokuNumber(int value, int row, int col) //用于设置数独棋盘当前布局的数值
{
    sudokuBoard[row][col] = value;
    return checkSudoku(); //设置好后进行数独规则状态判断，检验是否违反数独规则，返回检查结果
}

void Sudoku::deleteSudokuNumber(int row, int col) //把填入数独当前棋盘中的数值删除（需要原本为0)
{
    if (sudokuQuestion[row][col] == 0) //判断数独棋盘问题布局的该行列是否为0，若为0，则代表为回答填空处、非固定值可更改
        sudokuBoard[row][col] = 0;
}

Board Sudoku::DFS(int pos) //DFS搜索，查询当前棋盘布局下的答案
{
    if (pos == emptySite.size()) //当遍历到无空位的时候（进入DFS必须限制有且至少有一个空位）
    {
        DFSFlag = true;//判断DFS查询是否有返回结果
        return sudokuBoard; //返回当前的数独棋盘（即在玩家操作后继续运行仍能获得的正确答案）
    }
    int row = emptySite[pos].first; //获取空位列表的行值
    int col = emptySite[pos].second; //获取空位列表的列值
    for (int digit = 1; digit <= BOARDSIZE; digit++) //遍历可填入的数字
        if (!((rowUsed[row] | colUsed[col] | blockUsed[row / 3 * 3 + col / 3]) & (1 << digit)))//判断行列宫是否已有digit存在
        {
            sudokuBoard[row][col] = digit;//预填入sudokuBoard
            updateSudokuStatus(row, col, digit);//更新填入的查询状态
            DFS(pos + 1);//加深迭代递归
            updateSudokuStatus(row, col, digit);//再次更新（即取消填入）查询状态
            sudokuBoard[row][col] = 0;//删除预填入数据
        }
}
