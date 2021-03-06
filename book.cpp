#include "book.h"

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QPropertyAnimation>
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
    }//Set the coeffiecncies of quandratic trajectory ramdomly

    dir = x1 < x2 ? 1 : -1;

    v = 1.0 * (x2 - x1) / (5000+rand()%999);
    //Set speed randomly

    static const QString img[] = {":/piece_image/0.png)}", ":/piece_image/1.png)}"};
    setStyleSheet("QPushButton{border-image: url(" + img[rand() % 2]);
    // style of book, random book image

    QObject::connect(this, &book::clicked, this, &book::clickEvent);
    QObject::connect(this, &book::fallen, this, &book::deleteEvent);
}

void book::clickEvent()
{
    // avoiding malfunction caused by clicking a fading book
    if(deleted) return;
    deleted = true;

    // add id to signal to help identifactino while removing
    emit myClicked(id);

    QPropertyAnimation *anime = new QPropertyAnimation(this, "geometry");
    anime->setDuration(1000);
    anime->setStartValue(QRect(now_x, HEIGHT - now_y, 80, 100));
    anime->setEndValue(QRect(now_x, HEIGHT - now_y, 0, 0));
    anime->start();//Disappearing animation effect

    QObject::connect(anime, &QPropertyAnimation::finished, this, &QPushButton::close);
}//Click events

void book::deleteEvent()
{
    this->hide();
    deleted = true;
}//Eliminate events caused when one book falls

void book::move(double add_rate)
{
    my_time +=add_rate;
    now_x = x1 + my_time * v;
    now_y = - a * (now_x - x1) * (now_x - x2);//Current location
    if((dir == 1 && now_x > x2) || (dir == -1 && now_x < x2))
    {
        emit fallen();
    }//Determining whether to fall
    else
    {
        QPushButton::setGeometry(now_x, HEIGHT - now_y, 80, 100);
        this->show();
    }
}//Move events

