#include "book.h"

#include <QThread>
#include <QObject>
#include <QDebug>

const int WIDTH = 1000;
const int HEIGHT = 600;

book::book(QWidget *parent, int id, int my_time) : QPushButton(parent), id(id), my_begin_time(my_time)
{
    deleted = false;

    x1 = rand() % WIDTH;
    if(x1 < WIDTH / 2) x2 = WIDTH / 2 + rand() % (WIDTH / 2);
    else x2 = rand() % (WIDTH / 2);
    a = 0.3 * (HEIGHT / ((x2 - x1) * (x2 - x1) / 4));
    if(x1 == x2) {
        if(x1 == 0) ++x2;
        else --x1;
    }
//    qDebug() << x1 << ' ' << x2 << ' ' << a << Qt::endl;

    dir = x1 < x2 ? 1 : -1;

    // total on-screen time could be 1s, 1.5s or 3s
    v = 1.0 * (x2 - x1) / (2500+rand()%490);

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
    timer -= my_begin_time;
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
