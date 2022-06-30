#include "book.h"
#include "rank.h"
#include "game.h"
#include "confirm.h"
#include "mainwindow.h"

#include <bits/stdc++.h>
#include <QApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QFile>
#include <QDir>

using namespace std;

// to generate items
int numbers;
bool game_ended;
std::vector<book*> on_screen;

void game_over()
{
    game_ended = true;

    while(on_screen.size())
    {
        on_screen.back()->hide();
        on_screen.pop_back();
    }// Delete book

}// game over

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
    }// Find deleted books
    std::swap(on_screen[pos], on_screen[on_screen.size() - 1]);
    on_screen.pop_back(); ++numbers;// Score increase
}// The event of click

void T()
{
    qDebug() << "running" << Qt::endl;
}

QString rout;
void memorying(){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");
    QFile f(rout+"/grade.txt");
    f.open(QIODevice::Append|QIODevice::Text);
    QTextStream fout(&f);
    QByteArray cdata = current_date.toLocal8Bit();
    std::string cstr = std::string(cdata);
    fout.setFieldAlignment(QTextStream::AlignRight);
    fout.setFieldWidth(10);
    fout.setPadChar('0');
    fout<<numbers;
    fout.setFieldWidth(0);
    fout<<" "<<QString::fromStdString(cstr)<<"\n";
    f.close();
    numbers=0;
}
void gaming(Game *g)
{
    // time interval of item generation
    static const int generation_rate = 500;// Frequency of book occurrences
    static const int refresh_rate = 1;// refresh rate

    QObject::connect(g, &Game::gameEnd, game_over);

    QTimer *m_Timer = new QTimer;
    m_Timer->start(refresh_rate);
    QObject::connect(m_Timer, &QTimer::timeout, [=](){
        static int id = 0; // index of book
        static int timer = 0;// time
        static double v_up=1; // acceleration of speed

        if(game_ended) timer = 0, game_ended = 0, v_up = 1;

        if(timer % (generation_rate+1000) == generation_rate || !on_screen.size()){
            int Number = rand() % 3 + 2;
            while(Number -- && on_screen.size() < 6){
                book * new_item = new book(g, id++);
                on_screen.push_back(new_item);
                QObject::connect(new_item, &book::fallen, g, &Game::gameEnd);//Connect fallen and gameend
                QObject::connect(new_item, &book::myClicked, &clickEvent);
                QObject::connect(new_item, &book::myClicked, g, &Game::Clicked);
            }
        }//Generate new books

        ++timer;
        if(timer % (generation_rate * 10) == 0) v_up += 0.5;
        //Increased difficulty

        for(unsigned int i = 0; i < on_screen.size(); ++i)
        {
            on_screen[i]->move(v_up);
        }//move of book
    });
    QObject::connect(g, &Game::gameEnd, m_Timer, &QTimer::stop);
    memorying();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Rank r;
    Game g;
    Confirm c;
    w.show();

    QObject::connect(&w, &MainWindow::gameStart, &g, &Game::show);
    QObject::connect(&g, &Game::gameStart, &w, &MainWindow::changecur);//Mouse shape change
    QObject::connect(&g, &Game::gameStart, gaming);
    QObject::connect(&g, &Game::gameClosed, &w, &MainWindow::resetcur);//Mouse shape Recovery
    QObject::connect(&g, &Game::gameClosed, &w, &QWidget::show);
    QObject::connect(&g, &Game::gameClosed, memorying);

    QObject::connect(&w, &MainWindow::OpenRank, &r, &Rank::show);
    QObject::connect(&r, &Rank::rankClosed, &w, &QWidget::show);

    QObject::connect(&w, &MainWindow::tryclose, &c, &Confirm::show);
    QObject::connect(&c, &Confirm::Closed ,&w, &MainWindow::die);

    rout=QDir::currentPath();
    return a.exec();
}
