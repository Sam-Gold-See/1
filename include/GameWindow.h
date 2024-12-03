#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../include/Sudoku.h"
#include "../include/Operation.h"

#include <QTableWidgetItem>

namespace Ui
{
    class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = nullptr); //GameWindow窗口的构造函数，实现GameWindow窗口UI界面的生成
    ~GameWindow() override; //GameWindow窗口的析构函数，实现GameWindow窗口的销毁

private slots:
    void on_button1_clicked(); //绑定数字1按钮的信号与槽，实现数字1按钮的功能

    void on_button2_clicked(); //绑定数字2按钮的信号与槽，实现数字2按钮的功能

    void on_button3_clicked(); //绑定数字3按钮的信号与槽，实现数字3按钮的功能

    void on_button4_clicked(); //绑定数字4按钮的信号与槽，实现数字4按钮的功能

    void on_button5_clicked(); //绑定数字5按钮的信号与槽，实现数字5按钮的功能

    void on_button6_clicked(); //绑定数字6按钮的信号与槽，实现数字6按钮的功能

    void on_button7_clicked(); //绑定数字7按钮的信号与槽，实现数字7按钮的功能

    void on_button8_clicked(); //绑定数字8按钮的信号与槽，实现数字8按钮的功能

    void on_button9_clicked(); //绑定数字9按钮的信号与槽，实现数字9按钮的功能

    void on_buttonWithdraw_clicked(); //绑定撤回键按钮的信号与槽，实现撤回键按钮的功能

    void on_buttonRestart_clicked(); //绑定重开按钮的信号与槽，实现重开按钮的功能

    void on_buttonRubber_clicked(); //绑定橡皮擦按钮的信号与槽，实现橡皮擦按钮的功能

    void on_tableSudokuBoard_cellClicked(int row, int column); //绑定数独盘的行列选中效果，实现获得选中行列的位置信息效果

    void on_buttonExit_clicked(); //绑定退出键按钮的信号与槽，实现退出键按钮的功能

    void on_buttonAnswer_clicked(); //绑定显示答案按钮的信号与槽，实现显示答案按钮的功能

    void on_numberKeyPressed(int number); //绑定数字键按钮的信号与槽，实现键盘与功能按钮绑定

    void on_buttonCommit_clicked();

    void updateLCD(); //更新LCD计时器时间

private:
    Ui::GameWindow* ui;

    Sudoku sudoku; //创建数独对象
    Operation operationList; //创建操作栈对象
    QTimer* timer; //初始化一个QTimer对象

    int rowActive = -1; //用于存储选中的行（全局设置免传入，提高效率）
    int colActive = -1; //用于存储选中的列
    int timeCounter; //计时器值

    void initBoard(); //初始化棋盘对象（由于棋盘是会动态变化的，除了该棋盘和计时器之外，全用QtDesigner生成静态UI控件）
    void updateBoard(int value, int row, int col); //填入数字之后更新数独棋盘对象

    static QTableWidgetItem* initQTableWidgetItem(int value, bool isTrue); //将填入数据样式格式化为数独棋盘的样式
};

#endif // GAMEWINDOW_H
