#include "broken_book.h"

#include <QThread>
#include <QObject>
#include <QDebug>
#include <cmath>

const int WIDTH = 1000;
const int HEIGHT = 600;

book::book(QWidget *parent) : QPushButton(parent)
{
    deleted = false;

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
//        qDebug() << "show" << ' ' << x << ' ' << y << Qt::endl;
    }
}

QSize book::sizeHint() const
{
    return QSize(80, 100);
}
