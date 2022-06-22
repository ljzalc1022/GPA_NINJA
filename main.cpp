#include "mainwindow.h"
#include "book_controller.h"

#include <QApplication>
#include <QObject>
#include <QThread>
#include <QDebug>

// to generate items
bool game_ended;
void game_over()
{
    game_ended = true;
}
void gaming(Game *g)
{
    // time interval of item generation
    static const int generation_rate = 1000;

    QObject::connect(g, &Game::gameEnd, game_over);

//    while(!game_ended)
    for(int i = 1; i <= 2; ++i)
    {
        qDebug() << 1 << Qt::endl;

        QThread::msleep(generation_rate);

        book * new_item = new book(g);
        book_controller * controller = new book_controller(nullptr, new_item);
        controller->setStackSize(10 * 1024 * 1024);

        QObject::connect(g, &Game::gameEnd, new_item, &book::deleteEvent);
        QObject::connect(controller, &QThread::finished, new_item, &QObject::deleteLater);

        QObject::connect(new_item, &book::fallen, g, &Game::close);

        controller->start();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Game g;
    w.show();

    QObject::connect(&w, &MainWindow::gameStart, &g, &Game::show);
    QObject::connect(&g, &Game::gameStart, gaming);
    QObject::connect(&g, &Game::gameEnd, &w, &QWidget::show);

    return a.exec();
}
