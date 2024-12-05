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
      , timeCounter(0) //初始化计时器的数字为0
{
    setWindowIcon(QIcon(":/resources/LOGO.ico")); //设置GameWindow窗口的任务栏、窗口图标

    ui->setupUi(this); //初始化通过QtDesigner生成的静态UI

    initBoard(); //初始化棋盘对象（由于棋盘是会动态变化的，除了该棋盘和计时器之外，全用QtDesigner生成静态UI控件）

    for (int i = 1; i <= 9; ++i)
        new QShortcut(QKeySequence(QString::number(i)), this, [this, i]() { on_numberKeyPressed(i); },
                      Qt::WidgetWithChildrenShortcut); //绑定数字按键与相应按钮，设置接收键盘数字按键输出信号，实现双重触发

    setLabelModeLevel();

    ui->labelCorrect->setVisible(false); //设置正确结果弹窗的可见性为false
    ui->labelWrong->setVisible(false); //设置错误结果弹窗的可见性为true

    ui->lcdTime->setDigitCount(8); //设置LCD计时器的显示位数为8
    ui->lcdTime->setMode(QLCDNumber::Dec); //设置LCD计时器的显示模式

    timer = new QTimer(this); // 创建一个QTimer对象，并将其与当前对象(this)关联

    // 将定时器的timeout()信号连接到当前对象的updateLCD()槽函数
    // 当定时器溢出时（即每过一定时间间隔），updateLCD()槽函数将被调用
    connect(timer,SIGNAL(timeout()), this,SLOT(updateLCD()));

    timer->start(1000); // 启动定时器，设置其溢出间隔为1000毫秒（即1秒）
}

GameWindow::~GameWindow() // GameWindow窗口的析构函数调用
{
    delete ui; //GameWindow窗口的析构函数，实现GameWindow窗口的销毁
}

//GameWindow窗口的按钮函数绑定

void GameWindow::on_button1_clicked() //连接了按钮1的信号与槽，配置按键触发的配套函数
{
    updateBoard(1, rowActive, colActive); //对于选中的行列位置输入1
}

void GameWindow::on_button2_clicked() //连接了按钮2的信号与槽，配置按键触发的配套函数
{
    updateBoard(2, rowActive, colActive); //对于选中的行列位置输入2
}

void GameWindow::on_button3_clicked() //连接了按钮3的信号与槽，配置按键触发的配套函数
{
    updateBoard(3, rowActive, colActive); //对于选中的行列位输入3
}

void GameWindow::on_button4_clicked() //连接了按钮4的信号与槽，配置按键触发的配套函数
{
    updateBoard(4, rowActive, colActive); //对于选中的行列位输入4
}

void GameWindow::on_button5_clicked() //连接了按钮5的信号与槽，配置按键触发的配套函数
{
    updateBoard(5, rowActive, colActive); //对于选中的行列位输入5
}

void GameWindow::on_button6_clicked() //连接了按钮6的信号与槽，配置按键触发的配套函数
{
    updateBoard(6, rowActive, colActive); //对于选中的行列位输入6
}

void GameWindow::on_button7_clicked() //连接了按钮7的信号与槽，配置按键触发的配套函数
{
    updateBoard(7, rowActive, colActive); //对于选中的行列位输入7
}

void GameWindow::on_button8_clicked() //连接了按钮8的信号与槽，配置按键触发的配套函数
{
    updateBoard(8, rowActive, colActive); //对于选中的行列位输入8
}

void GameWindow::on_button9_clicked() //连接了按钮9的信号与槽，配置按键触发的配套函数
{
    updateBoard(9, rowActive, colActive); //对于选中的行列位输入9
}

void GameWindow::on_buttonWithdraw_clicked() //连接了撤回按钮的信号与槽，配置按键触发的配套函数
{
    operation temp = operationList.popOperation(); //获取Operation栈的顶部元素
    int row = temp.row; //分配读取到顶部元素的值
    int col = temp.col; //分配读取到顶部元素的值
    int value = temp.value; //分配读取到顶部元素的值
    bool isTrue = temp.isTrue; //分配读取到顶部元素的值
    if (row != -1 && col != -1) //特殊处理，保证值为正常，Operation栈未达栈底
    {
        QTableWidgetItem* item = ui->tableSudokuBoard->item(row, col); //读取数独棋盘对应行列存储的对象
        if (item)
            delete item;
        ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(value, isTrue)); //调整item格式存入当前数独棋盘UI中
    }
}

void GameWindow::on_buttonRestart_clicked() //连接了重开按钮的信号与槽，配置按键触发的配套函数
{
    sudoku.setSudokuBoard(sudoku.getSudokuQuestion()); //将后台的sudokuBoard对象初始化为预先存储的问题布局
    initBoard(); //更新当前UI棋盘布局
    while (true) //清空OperationList存储的值
    {
        operation temp = operationList.popOperation(); //循环pop出栈存储值
        if (temp.row == -1 && temp.col == -1) //直到pop出了违例数据，证明operation清空到了栈底
            break;
    }
    ui->buttonWithdraw->setVisible(true); //设置撤回按钮的可见性为true
    ui->buttonCommit->setVisible(true); //设置提交按钮的可见性为true
    ui->buttonAnswer->setVisible(true); //设置显示答案按钮的可见性为true
}

void GameWindow::on_buttonRubber_clicked() //连接了橡皮擦按钮的信号与槽，配置按键触发的配套函数
{
    if ((rowActive != -1 && colActive != -1) && sudoku.getSudokuQuestion()[rowActive][colActive] == 0)
    {
        operationList.pushOperation(rowActive, colActive, sudoku.getSudokuNumber(rowActive, colActive), true);
        ui->tableSudokuBoard->setItem(rowActive, colActive, initQTableWidgetItem(0, true));
    }
}

void GameWindow::on_tableSudokuBoard_cellClicked(int row, int column) //获取当前选中的棋盘布局选中行列
{
    rowActive = row; //设置选中的行
    colActive = column; //设置选中的列
}

void GameWindow::on_buttonExit_clicked() //连接了退出按钮的信号与槽，配置按键触发的配套函数
{
    MainWindow* mainWindow = new MainWindow(); //新建MainWindow窗口对象
    this->close(); //关闭当前GameWindow窗口
    mainWindow->show(); //设置新MainWindow窗口对象的可见性为true
}

void GameWindow::on_buttonAnswer_clicked() //连接了显示答案按钮的信号与槽，配置按键触发的配套函数
{
    ui->buttonWithdraw->setVisible(false); //设置撤回按钮的可见性为false
    ui->buttonCommit->setVisible(false); //设置提交按钮的可见性为false
    ui->buttonAnswer->setVisible(false); //设置显示答案按钮的可见性为false
    timer->stop(); //设置计时器暂停
    Board answer = sudoku.getSudokuAnswer(); //获取数独棋盘的答案
    std::vector<std::pair<int, int>> emptySite(0); //创建一个数组存储当前数独棋盘布局与答案不符合的行列值，便于后续更新样式
    for (int row = 0; row < Sudoku::BOARDSIZE; row++) //遍历行
        for (int col = 0; col < Sudoku::BOARDSIZE; col++) //遍历列
            if (answer[row][col] != sudoku.getSudokuNumber(row, col)) //当当前的棋盘布局数据和数独答案数据不匹配相等时，记录当前位置
                emptySite.push_back({row, col}); //存入当前数组末尾
    sudoku.setSudokuBoard(answer); //设置后台数据中的数独答案
    initBoard(); //刷新当前数独棋盘布局
    for (auto it = emptySite.begin(); it != emptySite.end(); it++) //遍历数组
    {
        int row = it->first; //获取对象行
        int col = it->second; //获取对象列
        ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(answer[row][col], false)); //设置当前行列显示值的样式为红加强
    }
}

void GameWindow::on_numberKeyPressed(int number) //连接按键信号与槽和数字按键
{
    switch (number) //配置数字按键触发的效果
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

void GameWindow::initBoard() //更新当前数独棋盘UI展示
{
    for (int row = 0; row < 9; row++) //行遍历
        for (int col = 0; col < 9; col++) //列遍历
            ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(sudoku.getSudokuNumber(row, col), true));
    //根据sudokuBoard存储的值，更新当前的UI棋盘布局的展示值
}

void GameWindow::updateBoard(int value, int row, int col) //更新数独棋盘
{
    if (row == -1 && col == -1) //如果行列值非法，则不更新
        return;
    int datum = sudoku.getSudokuNumber(row, col); //获取当前数独棋盘的数值
    if (sudoku.getSudokuQuestion()[row][col] == 0) //如果数独问题布局该值为0（即可以让玩家填充数字）
    {
        QTableWidgetItem* item = ui->tableSudokuBoard->item(row, col); //获取当前表格项
        if (item) // 如果表格项存在
        {
            QBrush brush = item->foreground(); // 获取当前表格项的前景色
            QColor color = brush.color(); // 从画刷中获取颜色
            operationList.pushOperation(row, col, datum, color == QColor(Qt::red));
            // 将当前操作推入操作列表，包括行、列、数据以及颜色是否为红色，即是否正确
        }
        bool isTrue = sudoku.setSudokuNumber(value, row, col); // 尝试在数独游戏中设置指定行和列的数字，返回值表示操作是否成功
        ui->tableSudokuBoard->setItem(row, col, initQTableWidgetItem(value, isTrue));
        // 在表格中设置新的项，使用初始化函数来创建一个带特定值的项,如果isTrue为真，表示颜色为黑，否则颜色为红
    }
}

QTableWidgetItem* GameWindow::initQTableWidgetItem(int value, bool isTrue) // 初始化QTableWidgetItem的函数，用于创建一个具有特定样式和值的表格项
{
    if (value == 0)
        return new QTableWidgetItem(""); //如果值为0，表示该单元格为空，返回一个空的表格项

    QTableWidgetItem* item = new QTableWidgetItem(QString::number(value)); // 创建一个新的表格项，并将其值设置为传入的数字

    QFont font = item->font(); // 获取当前表格项的字体，并设置为新样式
    font.setBold(true); // 设置字体为粗体
    font.setPointSize(28); // 设置字体大小为28点
    item->setFont(font); // 应用新的字体样式到表格项

    if (!isTrue) // 如果isTrue为假，表示该值是错误的，将文本颜色设置为红色
        item->setForeground(QBrush(Qt::red));

    item->setTextAlignment(Qt::AlignCenter); // 设置表格项的文本对齐方式为居中
    return item; // 返回创建并设置好的表格项
}

void GameWindow::on_buttonCommit_clicked() // 响应提交按钮点击事件的槽函数
{
    timer->stop(); // 停止计时器
    ui->buttonAnswer->setVisible(false); // 隐藏答案按钮
    if (sudoku.checkSudoku() && sudoku.checkEmptySite()) // 检查数独游戏是否正确完成，并且没有空位
        ui->labelCorrect->setVisible(true); // 如果数独游戏正确完成，显示正确标签
    else
        ui->labelWrong->setVisible(true); // 如果数独游戏有错误或者有空位，显示错误标签
    on_buttonAnswer_clicked();
}

void GameWindow::updateLCD() //更新计时器
{
    timeCounter++; //计时器技术增加

    int hours = timeCounter / 3600; //格式化小时数
    int minutes = timeCounter % 3600 / 60; //格式化分钟数
    int seconds = timeCounter % 60; //格式化秒数

    QString timeString = QString("%1:%2:%3") //格式化字符串显示
                         .arg(hours, 2, 10, QLatin1Char('0'))
                         .arg(minutes, 2, 10, QLatin1Char('0'))
                         .arg(seconds, 2, 10, QLatin1Char('0'));

    ui->lcdTime->display(timeString); //连接LCD计数器和计时字符串
}

void GameWindow::setLabelModeLevel()
{
    ui->labelModeLevel->setStyleSheet(
        QString("QLabel{border-image: url(:/resources/GameWindow/%1.png);}").arg(
            QString::fromStdString(Level::levelName))); //设置显示难度按钮的图源名字，通过读取Level类中存储的levelName提供
}
