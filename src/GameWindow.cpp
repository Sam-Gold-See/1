#include "../include/GameWindow.h"
#include "../include/Mainwindow.h"
#include "../include/Utils.h"
#include "../include/Level.h"
#include "../include/Operation.h"
#include "../ui/ui_GameWindow.h"

#include <QTimer>
#include <QShortcut>
#include <QTableWidget>

GameWindow::GameWindow(QWidget* parent)
    : QWidget(parent)
      , ui(new Ui::GameWindow)
      , timeCounter(0)
{
    setWindowIcon(QIcon(":/resources/LOGO.ico")); //设置GameWindow窗口的任务栏、窗口图标

    ui->setupUi(this); //初始化通过QtDesigner生成的静态UI

    initBoard(); //初始化棋盘对象（由于棋盘是会动态变化的，除了该棋盘和计时器之外，全用QtDesigner生成静态UI控件）

    ui->labelModeLevel->setStyleSheet(
        QString("QLabel{border-image: url(:/resources/GameWindow/%1.png);}").arg(
            QString::fromStdString(Level::levelName)));
    for (int i = 1; i <= 9; ++i)
        new QShortcut(QKeySequence(QString::number(i)), this, [this, i]() { on_numberKeyPressed(i); },
                      Qt::WidgetWithChildrenShortcut); //绑定数字按键与相应按钮，设置接收键盘数字按键输出信号，实现双重触发

    ui->lcdTime->setDigitCount(8);
    ui->lcdTime->setMode(QLCDNumber::Dec);

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()), this,SLOT(updateLCD()));

    timer->start(1000);
}

GameWindow::~GameWindow()
{
    delete ui; //GameWindow窗口的析构函数，实现GameWindow窗口的销毁
}

//GameWindow窗口的按钮函数绑定

void GameWindow::on_button1_clicked()
{
    updateBoard(1, rowActive, colActive);
}

void GameWindow::on_button2_clicked()
{
    updateBoard(2, rowActive, colActive);
}

void GameWindow::on_button3_clicked()
{
    updateBoard(3, rowActive, colActive);
}

void GameWindow::on_button4_clicked()
{
    updateBoard(4, rowActive, colActive);
}

void GameWindow::on_button5_clicked()
{
    updateBoard(5, rowActive, colActive);
}

void GameWindow::on_button6_clicked()
{
    updateBoard(6, rowActive, colActive);
}

void GameWindow::on_button7_clicked()
{
    updateBoard(7, rowActive, colActive);
}

void GameWindow::on_button8_clicked()
{
    updateBoard(8, rowActive, colActive);
}

void GameWindow::on_button9_clicked()
{
    updateBoard(9, rowActive, colActive);
}

void GameWindow::on_buttonWithdraw_clicked() //绑定
{
    operation temp = operationList.popOperation();
    int row = temp.row;
    int col = temp.col;
    int value = temp.value;
    bool isTrue = temp.isTrue;
    if (row != -1 && col != -1)
    {
        QTableWidgetItem* item = ui->tableSudokuBoard->item(row, col);
        if (item)
        {
            delete item;
        }
        ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(value, isTrue));
    }
}

void GameWindow::on_buttonRestart_clicked()
{
    sudoku.setSudokuBoard(sudoku.getSudokuQuestion());
    initBoard();
    while (true)
    {
        operation temp = operationList.popOperation();
        if (temp.row == -1 && temp.col == -1)
            break;
    }
    timeCounter = 0;
}

void GameWindow::on_buttonRubber_clicked()
{
    if ((rowActive != -1 && colActive != -1) && sudoku.getSudokuQuestion()[rowActive][colActive] == 0)
    {
        operationList.pushOperation(rowActive, colActive, sudoku.getSudokuNumber(rowActive, colActive), true);
        ui->tableSudokuBoard->setItem(rowActive, colActive, initQTableWidgetItem(0, true));
    }
}

void GameWindow::on_tableSudokuBoard_cellClicked(int row, int column)
{
    rowActive = row;
    colActive = column;
}

void GameWindow::on_buttonExit_clicked()
{
    MainWindow* mainWindow = new MainWindow();
    this->close();
    mainWindow->show();
}

void GameWindow::on_buttonAnswer_clicked()
{
    sudoku.setSudokuBoard(sudoku.getSudokuAnswer());
    initBoard();
}

void GameWindow::on_numberKeyPressed(int number)
{
    switch (number)
    {
    case 1: on_button1_clicked();
        break;
    case 2: on_button2_clicked();
        break;
    case 3: on_button3_clicked();
        break;
    case 4: on_button4_clicked();
        break;
    case 5: on_button5_clicked();
        break;
    case 6: on_button6_clicked();
        break;
    case 7: on_button7_clicked();
        break;
    case 8: on_button8_clicked();
        break;
    case 9: on_button9_clicked();
        break;
    default: break;
    }
}


void GameWindow::initBoard()
{
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
        {
            int value = sudoku.getSudokuNumber(row, col);
            ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(value, true));
        }
}

void GameWindow::updateBoard(int value, int row, int col)
{
    if (row == -1 && col == -1)
        return;
    int datum = sudoku.getSudokuNumber(row, col);
    if ((row != -1 && col != -1) && sudoku.getSudokuQuestion()[row][col] == 0)
    {
        QTableWidgetItem* item = ui->tableSudokuBoard->item(row, col);
        if (item)
        {
            QBrush brush = item->foreground();
            QColor color = brush.color();
            operationList.pushOperation(row, col, datum, color == QColor(Qt::red));
        }
        bool isTrue = sudoku.setSudokuNumber(value, row, col);
        ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(value, isTrue));
    }
}

QTableWidgetItem* GameWindow::initQTableWidgetItem(int value, bool isTrue)
{
    if (value == 0)
        return new QTableWidgetItem("");

    QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));

    QFont font = item->font();
    font.setBold(true);
    font.setPointSize(28);
    item->setFont(font);

    if (!isTrue)
        item->setForeground(QBrush(Qt::red));

    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void GameWindow::on_buttonCommit_clicked()
{
    timer->stop();
}

void GameWindow::updateLCD()
{
    timeCounter++;

    ui->lcdTime->display(timeCounter);
}
