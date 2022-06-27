#include "book.h"
#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>

// to generate items
bool game_ended;
const int MAX_onscreen = 3; // max number of books on screen
std::vector<book*> on_screen;
void game_over()
{
    game_ended = true;
}
void clickEvent(int id)
{
    int pos = -1;
    for(unsigned int i = 0; i < on_screen.size(); ++i)
    {
        if(on_screen[i]->id == id)
        {
            pos = i;
            break;
        }
    }
    std::swap(on_screen[pos], on_screen[on_screen.size() - 1]);
    on_screen.pop_back();
}
void T()
{
    qDebug() << "running" << Qt::endl;
}
void gaming(Game *g)
{
    // time interval of item generation
    static const int generation_rate = 30;
    static const int refresh_rate = 16;

    on_screen.clear();

    QObject::connect(g, &Game::gameEnd, game_over);

    QTimer *m_Timer = new QTimer;
    m_Timer->start(refresh_rate);
    QObject::connect(m_Timer, &QTimer::timeout, [=](){
        static int id = 0; // index of book
        static int timer = 0;

        ++timer;
        qDebug() << timer << ' ' << on_screen.size() << Qt::endl;

        if(timer % generation_rate == 0 && on_screen.size() < MAX_onscreen)
        {
            book * new_item = new book(g, id++);
            on_screen.push_back(new_item);
            QObject::connect(new_item, &book::fallen, game_over);
            QObject::connect(new_item, &book::fallen, m_Timer, &QTimer::stop);
            QObject::connect(new_item, &book::myClicked, &clickEvent);
        }
        for(unsigned int i = 0; i < on_screen.size(); ++i)
        {
            on_screen[i]->move(timer * generation_rate);
        }
    });
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
