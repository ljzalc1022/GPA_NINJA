#include "book.h"
#include "game.h"
#include "mainwindow.h"

#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>

// to generate items
bool game_ended;
std::vector<book*> on_screen;
std::vector<book*> delete_screen;
void game_over()
{
    game_ended = true;

    while(on_screen.size())
    {
        on_screen.back()->hide();
        on_screen.pop_back();
    }
    while(delete_screen.size())
    {
        delete_screen.back()->hide();
        delete_screen.pop_back();
    }
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
    delete_screen.push_back(on_screen.back());
    delete_screen.back()->setStyleSheet("background-color: yellow");
    delete_screen.back()->setEnabled(false);
    on_screen.pop_back();
}
void T()
{
    qDebug() << "running" << Qt::endl;
}
void gaming(Game *g)
{
    // time interval of item generation
    static const int generation_rate = 5000;
    static const int refresh_rate = 1;

    QObject::connect(g, &Game::gameEnd, game_over);

    QTimer *m_Timer = new QTimer;
    m_Timer->start(refresh_rate);
    QObject::connect(m_Timer, &QTimer::timeout, [=](){
        static int id = 0; // index of book
        static int timer = 0;
        static double v_up=1;
        if(game_ended) timer = 0, game_ended = 0, v_up = 1;

        if(timer % (generation_rate+1000) == generation_rate || !on_screen.size()){
            int Number = rand() % 3 + 2;
            while(Number -- && on_screen.size() < 6){
                book * new_item = new book(g, id++);
                on_screen.push_back(new_item);
                QObject::connect(new_item, &book::fallen, g, &Game::gameEnd);
                QObject::connect(new_item, &book::myClicked, &clickEvent);
            }
        }

        ++timer;
        if(timer % (generation_rate * 10) == 0) v_up += 0.5;
        //qDebug() << timer << ' ' << on_screen.size() << Qt::endl;

        for(unsigned int i = 0; i < on_screen.size(); ++i)
        {
            on_screen[i]->move(v_up);
        }

        while(delete_screen.size() > 10)
        {
            delete_screen[0]->hide();
            std::swap(delete_screen[0],delete_screen.back());
            delete_screen.pop_back();
        }

        for(unsigned int i = 0; i < delete_screen.size(); ++i)
        {
            delete_screen[i]->move(0);
        }
    });
    QObject::connect(g, &Game::gameEnd, m_Timer, &QTimer::stop);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Game g;
    w.show();

    QObject::connect(&w, &MainWindow::gameStart, &g, &Game::show);
    QObject::connect(&g, &Game::gameStart, gaming);
    QObject::connect(&g, &Game::gameClosed, &w, &QWidget::show);

    return a.exec();
}
