#include "book.h"
#include "rank.h"
#include "game.h"
#include "mainwindow.h"

#include <bits/stdc++.h>
#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QFile>

using namespace std;

// to generate items
int numbers;
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
    on_screen.pop_back(); ++numbers; //cerr<<"bingo "<<numbers<<endl;
}
void T()
{
    qDebug() << "running" << Qt::endl;
}
void gaming(Game *g)
{
    // time interval of item generation
    static const int generation_rate = 500;
    static const int refresh_rate = 1;

    QObject::connect(g, &Game::gameEnd, game_over);

    QTimer *m_Timer = new QTimer;
    m_Timer->start(refresh_rate);
    QObject::connect(m_Timer, &QTimer::timeout, [=](){
        static int id = 0; // index of book
        static int timer = 0;
        static double v_up=1; // acceleration of speed

        if(game_ended) timer = 0, game_ended = 0, v_up = 1;

        if(timer % (generation_rate+1000) == generation_rate || !on_screen.size()){
            int Number = rand() % 3 + 2;
            while(Number -- && on_screen.size() < 6){
                book * new_item = new book(g, id++);
                on_screen.push_back(new_item);
                QObject::connect(new_item, &book::fallen, g, &Game::gameEnd);
                QObject::connect(new_item, &book::myClicked, &clickEvent);
                QObject::connect(new_item, &book::myClicked, g, &Game::Clicked);
            }
        }

        ++timer;
        if(timer % (generation_rate * 10) == 0) v_up += 0.5;
        //Increased difficulty

        for(unsigned int i = 0; i < on_screen.size(); ++i)
        {
            on_screen[i]->move(v_up);
        }//move of book
    });
    QObject::connect(g, &Game::gameEnd, m_Timer, &QTimer::stop);

}
void memorying(){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
    std::ofstream fout("C:\\Users\\Yxs\\Desktop\\GPA_NINJA-nufukim-patch-1\\grade.txt",ios::app);
    QByteArray cdata = current_date.toLocal8Bit();
    std::string cstr = std::string(cdata);
    fout<<setw(10)<<setfill('0')<<numbers<<' '<<cstr<<endl;
    fout.close();
    numbers=0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Rank r;
    Game g;
    w.show();

    QObject::connect(&w, &MainWindow::gameStart, &g, &Game::show);
    QObject::connect(&g, &Game::gameStart, gaming);
    QObject::connect(&g, &Game::gameClosed, &w, &QWidget::show);
    QObject::connect(&g, &Game::gameClosed, memorying);

    QObject::connect(&w, &MainWindow::OpenRank, &r, &Rank::show);
    QObject::connect(&r, &Rank::rankClosed, &w, &QWidget::show);

    QFile f(":/grade/grade.txt");
    if(!f.open(QIODevice::Append|QIODevice::Text)) cerr<<"???\n";
    QTextStream fout(&f);
    fout<<"write successfully\n";

    return a.exec();
}
