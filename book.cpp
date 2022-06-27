#include "book.h"

#include <QThread>
#include <QObject>
#include <QDebug>

const int WIDTH = 1000;
const int HEIGHT = 600;

book::book(QWidget *parent, int id) : QPushButton(parent), id(id)
{
    deleted = false;

    x1 = rand() % WIDTH;
    x2 = rand() % WIDTH;
    a = ((double)rand() / RAND_MAX) * (HEIGHT / ((x2 - x1) * (x2 - x1) / 4));
    if(x1 == x2) {
        if(x1 == 0) ++x2;
        else --x1;
    }
//    qDebug() << x1 << ' ' << x2 << ' ' << a << Qt::endl;

    dir = x1 < x2 ? 1 : -1;

    // total on-screen time could be 1s, 1.5s or 3s
    v = (x2 - x1) * (double(rand() % 3 + 1) / 3);
    v /= 1000;
    v /= 10;

    // style of book
    setStyleSheet("background-color: red");

    QObject::connect(this, &book::clicked, this, &book::clickEvent);
    QObject::connect(this, &book::fallen, this, &book::deleteEvent);
}

void book::clickEvent()
{
    emit myClicked(id);
    this->hide();
}
void book::deleteEvent()
{
//   qDebug() << "hidden" << Qt::endl;
    this->hide();
    deleted = true;
}

void book::move(int timer)
{
    int x = x1 + timer * v;
    int y = - a * (x - x1) * (x - x2);
    if((dir == 1 && x > x2) || (dir == -1 && x < x2))
    {
        emit fallen();
    }
    else
    {
        QPushButton::move(x, HEIGHT - y);
        this->show();
//        qDebug() << "show" << ' ' << x << ' ' << y << Qt::endl;
    }
}

QSize book::sizeHint() const
{
    return QSize(80, 100);
}
