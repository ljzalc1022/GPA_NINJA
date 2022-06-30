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

#define MAX_ON_SCREEN 6 // max books on screen

using namespace std;

// to generate items
int numbers;
bool game_ended; // flag to help clearing up for next game
std::vector<book*> on_screen; // unclicked books

void game_over()
{
    game_ended = true;

    while(on_screen.size())
    {
        on_screen.back()->hide();
        on_screen.pop_back();
    }// Delete all books

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
    }
    std::swap(on_screen[pos], on_screen[on_screen.size() - 1]);
    on_screen.pop_back();
    // Find clicked book and delete it

    ++numbers;// Score increase
}// The event of click

QString rout;
void memorying(){
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ddd");//get the date and time string

    QFile f(rout+"/grade.txt");
    f.open(QIODevice::Append|QIODevice::Text);
    QTextStream fout(&f);                                             //qfile operations

    QByteArray cdata = current_date.toLocal8Bit();
    std::string cstr = std::string(cdata);                            //get the score stirng

    fout.setFieldAlignment(QTextStream::AlignRight);
    fout.setFieldWidth(10);
    fout.setPadChar('0');
    fout<<numbers;
    fout.setFieldWidth(0);
    fout<<" "<<QString::fromStdString(cstr)<<"\n";                    //set the form of the string and output
    f.close();
    numbers=0;
}
void gaming(Game *g) // one game
{
    // time interval of item generation
    static const int generation_rate = 500;// Frequency of book occurrences
    static const int refresh_rate = 1;// refresh rate

    QObject::connect(g, &Game::gameEnd, game_over);

    QTimer *m_Timer = new QTimer; // use QTimer to refresh game regularily
    m_Timer->start(refresh_rate);
    QObject::connect(m_Timer, &QTimer::timeout, [=](){
        static int id = 0; // index of book
        static int timer = 0;// time recorder
        static double v_up=1; // acceleration of speed

        if(game_ended) // aka this is a replay
            timer = 0, game_ended = 0, v_up = 1;

        if(timer % (generation_rate+1000) == generation_rate || !on_screen.size()){ // gerate new books when no book is on screen or it's time
            int Number = rand() % 3 + 2;
            while(Number -- && on_screen.size() < MAX_ON_SCREEN){
                book * new_item = new book(g, id++);
                on_screen.push_back(new_item);
                QObject::connect(new_item, &book::fallen, g, &Game::gameEnd);//Connect fallen and gameend
                QObject::connect(new_item, &book::myClicked, &clickEvent); // deleting book and updating score-to-storage
                QObject::connect(new_item, &book::myClicked, g, &Game::Clicked); // updating score-to-show
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
    QObject::connect(&g, &Game::gameClosed, &w, &QWidget::show);
    // the two will never meet together, sad..

    QObject::connect(&g, &Game::gameStart, &w, &MainWindow::changecur);//Mouse shape change
    QObject::connect(&g, &Game::gameClosed, &w, &MainWindow::resetcur);//Mouse shape Recovery

    QObject::connect(&g, &Game::gameStart, gaming); // start game

    QObject::connect(&g, &Game::gameClosed, memorying);//if exit unusually,check the score and update the rank

    QObject::connect(&w, &MainWindow::OpenRank, &r, &Rank::show);//open the rank list
    QObject::connect(&r, &Rank::rankClosed, &w, &QWidget::show);//close the rank list and come back

    QObject::connect(&w, &MainWindow::tryclose, &c, &Confirm::show);//open the confirming window if the user wants to exit
    QObject::connect(&c, &Confirm::Closed ,&w, &MainWindow::die);//exit

    rout=QDir::currentPath();
    return a.exec();
}
