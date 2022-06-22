#include "book.h"

#include <QThread>
#include <QObject>
#include <QDebug>

const int WIDTH = 1000;
const int HEIGHT = 600;

book::book(QWidget *parent) : QPushButton(parent)
{
    deleted = false;

    x1 = rand() % WIDTH;
    x2 = rand() % WIDTH;
    a = ((double)rand() / RAND_MAX) * (HEIGHT / ((x2 - x1) * (x2 - x1) / 4));
    if(x1 == x2) {
        if(x1 == 0) ++x2;
        else --x1;
    }
    qDebug() << x1 << ' ' << x2 << ' ' << a << Qt::endl;

    dir = x1 < x2 ? 1 : -1;

    // total on-screen time could be 1s, 1.5s or 3s
    v = (x2 - x1) * (double(rand() % 3 + 1) / 3);
    v /= 1000;

    // style of book
    setStyleSheet("background-color: red");
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);


    QObject::connect(this, &book::clicked, this, &book::deleteEvent);
    QObject::connect(this, &book::fallen, this, &book::deleteEvent);
}

void book::deleteEvent()
{
    this->hide();
    deleted = true;
}

bool book::cal_pos(double &x, double &y, int timer)
{
    x = x1 + timer * v;
    y = - a * (x - x1) * (x - x2);
    if((dir == 1 && x > x2) || (dir == -1 && x < x2))
    {
        emit fallen();
        return true;
    }
    else return false;
}

QSize book::sizeHint() const
{
    return QSize(80, 100);
}
