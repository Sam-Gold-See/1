#include "include/MainWindow.h"
#include "include/GameWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    GameWindow y;
    y.show();
    return QApplication::exec();
}
