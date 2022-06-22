#include "book_controller.h"

#include <QThread>
#include <QDebug>

book_controller::book_controller(QObject *parent, book* entity) : QThread(parent), entity(entity)
{
}

book_controller::~book_controller()
{
}

void book_controller::run()
{
    // time interval of refreshing
    static const int refresh_time = 16;

    entity->show();

    int timer = 0;
    while(!entity->deleted)
    {
//        qDebug() << entity->deleted << Qt::endl;

        QThread::msleep(refresh_time);
        timer += refresh_time;

        double x, y;
        if(entity->cal_pos(x, y, timer))
        {
            break;
        }

//        qDebug() << timer << ' ' << x << ' ' << y << Qt::endl;
        entity->move((int)x, 600 - (int)y);
    }
}
