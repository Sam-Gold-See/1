#include "../include/Mainwindow.h"
#include "../ui/ui_MainWindow.h"
#include "../include/GameWindow.h"
#include "../include/Utils.h"
#include "../include/Level.h"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
      , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(":/resources/LOGO.ico"));

    ui->setupUi(this);

    ui->buttonIntroText->setVisible(false);
    ui->buttonLoveText->setVisible(false);
    ui->buttonLogoPressed->setVisible(false);

    Utils::initUtils();

    Level::setLevel(1);
    selectFlag = false;
    setButtonModeVisible(selectFlag);
    moveButtonModeTogether();
    ui->buttonModeEasy->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonStart_clicked()
{
    GameWindow* gameWindow = new GameWindow();
    this->close();
    gameWindow->show();
}

void MainWindow::on_buttonLove_clicked() const
{
    ui->buttonLoveText->setVisible(true);
}

void MainWindow::on_buttonIntro_clicked() const
{
    ui->buttonIntroText->setVisible(true);
}

void MainWindow::on_buttonLoveText_clicked() const
{
    ui->buttonLoveText->setVisible(false);
}

void MainWindow::on_buttonIntroText_clicked() const
{
    ui->buttonIntroText->setVisible(false);
}

void MainWindow::on_buttonBackground_clicked()
{
    ui->buttonLoveText->setVisible(false);
    ui->buttonIntroText->setVisible(false);
    ui->buttonLogoPressed->setVisible(false);
    ui->buttonLogo->setVisible(true);
}

void MainWindow::on_buttonModeHell_clicked()
{
    if (selectFlag)
    {
        Level::setLevel(4);
        selectFlag = false;
        setButtonModeVisible(selectFlag);
        moveButtonModeTogether();
        ui->buttonModeHell->setVisible(true);
    }
    else
    {
        selectFlag = true;
        moveButtonModeSeparately();
        setButtonModeVisible(selectFlag);
    }
}

void MainWindow::on_buttonModeHard_clicked()
{
    if (selectFlag)
    {
        Level::setLevel(3);
        selectFlag = false;
        setButtonModeVisible(selectFlag);
        moveButtonModeTogether();
        ui->buttonModeHard->setVisible(true);
    }
    else
    {
        selectFlag = true;
        moveButtonModeSeparately();
        setButtonModeVisible(selectFlag);
    }
}

void MainWindow::on_buttonModeNormal_clicked()
{
    if (selectFlag)
    {
        Level::setLevel(2);
        selectFlag = false;
        setButtonModeVisible(selectFlag);
        moveButtonModeTogether();
        ui->buttonModeNormal->setVisible(true);
    }
    else
    {
        selectFlag = true;
        moveButtonModeSeparately();
        setButtonModeVisible(selectFlag);
    }
}

void MainWindow::on_buttonModeEasy_clicked()
{
    if (selectFlag)
    {
        Level::setLevel(1);
        selectFlag = false;
        setButtonModeVisible(selectFlag);
        moveButtonModeTogether();
        ui->buttonModeEasy->setVisible(true);
    }
    else
    {
        selectFlag = true;
        moveButtonModeSeparately();
        setButtonModeVisible(selectFlag);
    }
}

void MainWindow::setButtonModeVisible(bool selectFlag) const
{
    ui->buttonModeEasy->setVisible(selectFlag);
    ui->buttonModeNormal->setVisible(selectFlag);
    ui->buttonModeHard->setVisible(selectFlag);
    ui->buttonModeHell->setVisible(selectFlag);
}

void MainWindow::moveButtonModeTogether() const
{
    ui->buttonModeEasy->move(togetherX, togetherY);
    ui->buttonModeNormal->move(togetherX, togetherY);
    ui->buttonModeHard->move(togetherX, togetherY);
    ui->buttonModeHell->move(togetherX, togetherY);
}

void MainWindow::moveButtonModeSeparately() const
{
    ui->buttonModeEasy->move(280, 465);
    ui->buttonModeNormal->move(645, 465);
    ui->buttonModeHard->move(280, 570);
    ui->buttonModeHell->move(645, 570);
}

void MainWindow::on_buttonLogo_clicked()
{
    ui->buttonLogo->setVisible(false);
    ui->buttonLogoPressed->setVisible(true);
}

void MainWindow::on_buttonLogoPressed_clicked()
{
    ui->buttonLogo->setVisible(true);
    ui->buttonLogoPressed->setVisible(false);
}

