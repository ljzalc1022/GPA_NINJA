#include "book.h"

#include <QThread>
#include <QObject>
#include <QDebug>
#include <cmath>

const int WIDTH = 1000;
const int HEIGHT = 600;

book::book(QWidget *parent, int id) : QPushButton(parent), id(id)
{
    deleted = false;

    x1 = rand() % WIDTH;
    if(x1 < WIDTH / 2) x2 = WIDTH / 2 + rand() % (WIDTH / 2);
    else x2 = rand() % (WIDTH / 2);
    a = (0.75 + 0.1 * (rand()%10 / 10)) * (HEIGHT / ((x2 - x1) * (x2 - x1) / 4));
    while( abs(x1-x2)<=100 ){
        x1 = rand() % WIDTH;
        if(x1 < WIDTH / 2) x2 = WIDTH / 2 + rand() % (WIDTH / 2);
        else x2 = rand() % (WIDTH / 2);
        a = (0.75 + 0.1 * (rand()%10 / 10)) * (HEIGHT / ((x2 - x1) * (x2 - x1) / 4));
    }//Set the horizontal coordinates of the start and end points

    dir = x1 < x2 ? 1 : -1;

    v = 1.0 * (x2 - x1) / (5000+rand()%999);
    //Set speed

    setStyleSheet("background-color: red");
    // style of book

    QObject::connect(this, &book::clicked, this, &book::clickEvent);
    QObject::connect(this, &book::fallen, this, &book::deleteEvent);
}

void book::clickEvent()
{
    emit myClicked(id);
    this->hide();
}//Click events

void book::deleteEvent()
{
    this->hide();
    deleted = true;
}//Eliminate events

void book::move(double add_rate)
{
    my_time +=add_rate;
    int x = x1 + my_time * v;
    int y = - a * (x - x1) * (x - x2);
    if((dir == 1 && x > x2) || (dir == -1 && x < x2))
    {
        emit fallen();
    }
    else
    {
        QPushButton::move(x, HEIGHT - y);
        this->show();
    }
}//Move events

QSize book::sizeHint() const
{
    return QSize(80, 100);
}//size of book
