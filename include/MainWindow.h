#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);//MainWindow窗口构造函数
    ~MainWindow();//MainWindow的窗口析构函数

private slots:
    void on_buttonStart_clicked();//连接开始游戏按钮的信号与槽

    void on_buttonLove_clicked() const;//连接爱心按钮的信号与槽

    void on_buttonIntro_clicked() const;//连接问号按钮的信号与槽

    void on_buttonLoveText_clicked() const;//连接爱心按钮生成弹窗的信号与槽

    void on_buttonIntroText_clicked() const;//连接问号按钮生成弹窗的信号与槽

    void on_buttonBackground_clicked();//连接背景窗口的信号与槽

    void on_buttonModeHell_clicked();//连接地狱难度按钮的信号与槽

    void on_buttonModeHard_clicked();//连接困难难度按钮的信号与槽

    void on_buttonModeNormal_clicked();//连接一般难度按钮的信号与槽

    void on_buttonModeEasy_clicked();//连接简单难度按钮的信号与槽

    void setButtonModeVisible(bool flag) const;//设置难度选择按钮的可视化程度

    void moveButtonModeTogether() const;//设置难度选择按钮移动至同一个位置

    void moveButtonModeSeparately() const;//设置难度选择按钮分开到四个位置

    void on_buttonLogo_clicked();//设置左上角Logo按钮触发后的效果

    void on_buttonLogoPressed_clicked();//设置中间大Logo生成后的操作效果

private:
    Ui::MainWindow* ui;
    bool selectFlag;//难度选择系列按钮是否被点击过
    const int togetherX = 462;//难度选择按钮的未点击状态X
    const int togetherY = 491;//难度选择按钮的未点击状态Y

};
#endif // MAINWINDOW_H
