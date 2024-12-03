#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../include/Sudoku.h"

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

    void on_button8_clicked();

    void on_button9_clicked();

    void on_buttonWithdraw_clicked();

    void on_buttonRestart_clicked();

    void on_buttonRubber_clicked();

    void on_tableSudokuBoard_cellClicked(int row, int column);

    void on_buttonExit_clicked();

    void on_buttonAnswer_clicked();

private:
    Ui::GameWindow *ui;

    Sudoku sudoku;
    int rowActive = -1;
    int colActive = -1;

    void initBoard();//
    void updateBoard(int value);//

    QTableWidgetItem* initQTableWidgetItem(int value, bool isTrue);
};

#endif // GAMEWINDOW_H
