#include "../include/Mainwindow.h"
#include "../ui/ui_MainWindow.h"
#include "../include/GameWindow.h"
#include "../include/Utils.h"
#include "../include/Level.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
      , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/resources/LOGO.ico")); //设置任务栏和窗口的Logo

    ui->setupUi(this); //显示MainWindow的所有静态设置UI

    ui->buttonIntroText->setVisible(false); //使得Intro弹窗先消失
    ui->buttonLoveText->setVisible(false); //使得Love弹窗先消失
    ui->buttonLogoPressed->setVisible(false); //使得Logo巨大化弹窗先消失

    Utils::initUtils(); //初始化Utils类，即给rand()随机类提供随机种子

    selectFlag = false; //初始化难度选择按钮的点击状态，默认为未点击状态隐藏，即false
    setButtonModeVisible(selectFlag); //设置四个难度按钮均隐藏
    moveButtonModeTogether(); //设置四个难度选择按钮重叠
    Level::setLevel(1);
    ui->buttonModeEasy->setVisible(true); //默认初始为简单难度，简单难度按钮可见
}

MainWindow::~MainWindow() //MainWindow的析构函数
{
    delete ui; //删除MainWindow的静态UI界面
}

void MainWindow::on_buttonStart_clicked() //连接了和开始按钮的信号与槽，设置该按钮触发的函数状态
{
    GameWindow* gameWindow = new GameWindow(); //设置GameWindow显现
    this->close(); //关闭当前窗口，启用MainWindow的析构函数
    gameWindow->show(); //设置刚生成的GameWindow的可见性为true
}

void MainWindow::on_buttonLove_clicked() const //连接了和爱心按钮的信号与槽，设置该按钮触发的函数状态
{
    ui->buttonLoveText->setVisible(true); //设置了爱心文案弹窗的可见性为true
    ui->buttonLogo->setVisible(false); //设置左上角小logo的可见性为false
    ui->buttonIntro->setVisible(false);//设置右下角问号按钮的可见性为false
    ui->buttonLove->setVisible(false);//设置右上角爱心的按钮的可见性为false
}

void MainWindow::on_buttonIntro_clicked() const //连接了和问号按钮的信号与槽，设置该按钮触发的函数状态
{
    ui->buttonIntroText->setVisible(true); //设置了问号文案弹窗的可见性为true
    ui->buttonLogo->setVisible(false); //设置左上角小logo的可见性为false
    ui->buttonIntro->setVisible(false);//设置右下角问号按钮的可见性为false
    ui->buttonLove->setVisible(false);//设置右上角爱心的按钮的可见性为false
}

void MainWindow::on_buttonLoveText_clicked() const //连接了和爱心文案弹窗的信号与槽，设置该按钮触发的函数状态
{
    ui->buttonLoveText->setVisible(false); //设置了爱心文案弹窗的可见性为false
    ui->buttonLogoPressed->setVisible(false); //设置logo巨大化版的可见性为false
    ui->buttonLogo->setVisible(true); //设置左上角小logo的可见性为true
    ui->buttonIntro->setVisible(true);//设置右下角问号按钮的可见性为true
    ui->buttonLove->setVisible(true);//设置右上角爱心的按钮的可见性为true
}

void MainWindow::on_buttonIntroText_clicked() const //连接了和问号文案弹窗的信号与槽，设置该按钮触发的函数状态
{
    ui->buttonIntroText->setVisible(false); //设置了问号文案弹窗的可见性为false
    ui->buttonLogo->setVisible(true); //设置左上角小logo的可见性为true
    ui->buttonIntro->setVisible(true);//设置右下角问号按钮的可见性为true
    ui->buttonLove->setVisible(true);//设置右上角爱心的按钮的可见性为true
}

void MainWindow::on_buttonBackground_clicked() //连接了和背景窗口的信号与槽，设置该窗口点击触发的函数状态
{
    ui->buttonLoveText->setVisible(false); //设置了爱心文案弹窗的可见性为false
    ui->buttonIntroText->setVisible(false); //设置了问号文案弹窗的可见性为false
    ui->buttonLogoPressed->setVisible(false); //设置了巨大化Logo弹窗的可见性为false
    ui->buttonLogo->setVisible(true); //设置了左上角小logo弹窗的可见性为true
    ui->buttonIntro->setVisible(true);//设置右下角问号按钮的可见性为true
    ui->buttonLove->setVisible(true);//设置右上角爱心的按钮的可见性为true
}

void MainWindow::on_buttonModeHell_clicked() //设置地狱难度按钮的触发效果
{
    if (selectFlag) //如果是选择难度状态
    {
        Level::setLevel(4); //设置Level类的难度为4
        selectFlag = false; //设置选择难度状态的布尔值为false，即非难度选择状态
        setButtonModeVisible(selectFlag); //设置所有难度按钮的可见性为false
        moveButtonModeTogether(); //设置四个难度按钮的位置统一
        ui->buttonModeHell->setVisible(true); //设置地狱难度按钮的可见性为true
    }
    else //如果非难度选择状态
    {
        selectFlag = true; //设置选择难度状态的布尔值为true，即处于难度选择状态
        moveButtonModeSeparately(); //设置四个难度选择按钮的坐标分离
        setButtonModeVisible(selectFlag); //设置四个难度按钮的可见性为true
    }
}

void MainWindow::on_buttonModeHard_clicked() //设置困难难度按钮的触发效果
{
    if (selectFlag) //如果是难度选择状态
    {
        Level::setLevel(3); //设置Level类的难度为3
        selectFlag = false; //设置选择难度状态的布尔值为false，即非难度选择状态
        setButtonModeVisible(selectFlag); //设置所有难度选择按钮的可见性为false
        moveButtonModeTogether(); //设置四个难度按钮的位置统一
        ui->buttonModeHard->setVisible(true); //设置困难难度按钮的可见性为true
    }
    else //如果非难度选择状态
    {
        selectFlag = true; //设置选择难度状态的布尔值为true，即处于难度选择状态
        moveButtonModeSeparately(); //设置四个难度选择按钮的坐标分离
        setButtonModeVisible(selectFlag); //设置四个难度按钮的可见性为true
    }
}

void MainWindow::on_buttonModeNormal_clicked() //设置一般难度按钮的触发效果
{
    if (selectFlag) //如果是难度选择状态
    {
        Level::setLevel(2); //设置Level类的难度为2
        selectFlag = false; //设置选择难度状态的布尔值为false，即非难度选择状态
        setButtonModeVisible(selectFlag); //设置所有难度选择按钮的可见性为false
        moveButtonModeTogether(); //设置四个难度按钮的位置统一
        ui->buttonModeNormal->setVisible(true); //设置一般难度按钮的可见性为true
    }
    else //如果非难度选择状态
    {
        selectFlag = true; //设置选择难度状态的布尔值为true，即处于难度选择状态
        moveButtonModeSeparately(); //设置四个难度选择按钮的坐标分离
        setButtonModeVisible(selectFlag); //设置四个难度按钮的可见性为true
    }
}

void MainWindow::on_buttonModeEasy_clicked() //设置简单难度按钮的触发效果
{
    if (selectFlag) //如果是难度选择状态
    {
        Level::setLevel(1); //设置Level类的难度为4
        selectFlag = false; //设置选择难度状态的布尔值为false，即非难度选择状态
        setButtonModeVisible(selectFlag); //设置所有难度选择按钮的可见性为false
        moveButtonModeTogether(); //设置四个难度按钮的位置统一
        ui->buttonModeEasy->setVisible(true); //设置困难难度按钮的可见性为true
    }
    else //如果非难度选择状态
    {
        selectFlag = true; //设置选择难度状态的布尔值为true，即处于难度选择状态
        moveButtonModeSeparately(); //设置四个难度选择按钮的坐标分离
        setButtonModeVisible(selectFlag); //设置四个难度按钮的可见性为true
    }
}

void MainWindow::setButtonModeVisible(bool selectFlag) const //统一四个难度按钮的可见性设置
{
    ui->buttonModeEasy->setVisible(selectFlag);
    ui->buttonModeNormal->setVisible(selectFlag);
    ui->buttonModeHard->setVisible(selectFlag);
    ui->buttonModeHell->setVisible(selectFlag);
}

void MainWindow::moveButtonModeTogether() const //统一四个难度按钮的坐标XY
{
    ui->buttonModeEasy->move(togetherX, togetherY);
    ui->buttonModeNormal->move(togetherX, togetherY);
    ui->buttonModeHard->move(togetherX, togetherY);
    ui->buttonModeHell->move(togetherX, togetherY);
}

void MainWindow::moveButtonModeSeparately() const //将四个难度选择按钮依次分开至四个位置
{
    ui->buttonModeEasy->move(280, 465);
    ui->buttonModeNormal->move(645, 465);
    ui->buttonModeHard->move(280, 570);
    ui->buttonModeHell->move(645, 570);
}

void MainWindow::on_buttonLogo_clicked() //连接了和logo按钮的信号与槽，设置该按钮触发的函数状态
{
    ui->buttonLogoPressed->setVisible(true); //设置logo巨大化版的可见性为true
    ui->buttonLogo->setVisible(false); //设置左上角小logo的可见性为false
    ui->buttonIntro->setVisible(false);//设置右下角问号按钮的可见性为false
    ui->buttonLove->setVisible(false);//设置右上角爱心的按钮的可见性为false
}

void MainWindow::on_buttonLogoPressed_clicked() //连接了和logo巨大化版的信号与槽，设置该按钮触发的函数状态
{
    ui->buttonLogoPressed->setVisible(false); //设置logo巨大化版的可见性为false
    ui->buttonLogo->setVisible(true); //设置左上角小logo的可见性为true
    ui->buttonIntro->setVisible(true);//设置右下角问号按钮的可见性为true
    ui->buttonLove->setVisible(true);//设置右上角爱心的按钮的可见性为true
}
