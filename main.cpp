#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Game g;
    w.show();
    QObject::connect(&w, &MainWindow::gameStart, &g, &QWidget::show);
    QObject::connect(&g, &Game::gameEnd, &w, &QWidget::show);
    return a.exec();
}
