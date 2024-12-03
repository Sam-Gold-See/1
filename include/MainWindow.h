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
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonStart_clicked();

    void on_buttonLove_clicked() const;

    void on_buttonIntro_clicked() const;

    void on_buttonLoveText_clicked() const;

    void on_buttonIntroText_clicked() const;

    void on_buttonBackground_clicked();

    void on_buttonModeHell_clicked();

    void on_buttonModeHard_clicked();

    void on_buttonModeNormal_clicked();

    void on_buttonModeEasy_clicked();

    void setButtonModeVisible(bool flag) const;

    void moveButtonModeTogether() const;

    void moveButtonModeSeparately() const;

    void on_buttonLogo_clicked();

    void on_buttonLogoPressed_clicked();

private:
    Ui::MainWindow* ui;
    bool selectFlag;
    const int togetherX = 462;
    const int togetherY = 491;

};
#endif // MAINWINDOW_H
