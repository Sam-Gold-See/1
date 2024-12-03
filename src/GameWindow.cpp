#include "../include/GameWindow.h"
#include "../include/Mainwindow.h"
#include "../include/Utils.h"
#include "../include/Operation.h"
#include "../ui/ui_GameWindow.h"

#include <iostream>
#include <QTableWidget>

GameWindow::GameWindow(QWidget* parent)
    : QWidget(parent)
      , ui(new Ui::GameWindow)
{
    setWindowIcon(QIcon(":/resources/LOGO.ico"));

    ui->setupUi(this);
    Operation operation;
    initBoard();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_button1_clicked()
{
    updateBoard(1);
}

void GameWindow::on_button2_clicked()
{
    updateBoard(2);
}

void GameWindow::on_button3_clicked()
{
    updateBoard(3);
}

void GameWindow::on_button4_clicked()
{
    updateBoard(4);
}

void GameWindow::on_button5_clicked()
{
    updateBoard(5);
}

void GameWindow::on_button6_clicked()
{
    updateBoard(6);
}

void GameWindow::on_button7_clicked()
{
    updateBoard(7);
}

void GameWindow::on_button8_clicked()
{
    updateBoard(8);
}

void GameWindow::on_button9_clicked()
{
    updateBoard(9);
}

void GameWindow::on_buttonWithdraw_clicked()
{
}

void GameWindow::on_buttonRestart_clicked()
{
    sudoku.setSudokuBoard(sudoku.getSudokuQuestion());
    initBoard();
}

void GameWindow::on_buttonRubber_clicked()
{
    if ((rowActive != -1 || colActive != -1) && sudoku.getSudokuQuestion()[rowActive][colActive] == 0)
    {
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

void GameWindow::initBoard()
{
    for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++)
            ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(sudoku.getSudokuNumber(row, col), true));
}

void GameWindow::updateBoard(int value)
{
    if ((rowActive != -1 || colActive != -1) && sudoku.getSudokuQuestion()[rowActive][colActive] == 0)
    {
        bool isTrue = sudoku.setSudokuNumber(value, rowActive, colActive);
        ui->tableSudokuBoard->setItem(rowActive, colActive, initQTableWidgetItem(value, isTrue));
    }
}

QTableWidgetItem* GameWindow::initQTableWidgetItem(int value, bool isTrue)
{
    QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));

    QFont font = item->font();
    font.setBold(true);
    font.setPointSize(12);
    item->setFont(font);

    if (!isTrue)
        item->setForeground(QBrush(Qt::red));

    item->setTextAlignment(Qt::AlignCenter);
    return item;
}
