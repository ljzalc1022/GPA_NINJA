#ifndef BOOK_H
#define BOOK_H

#endif // BOOK_H

#include <QPushButton>

class book: public QPushButton
{
    Q_OBJECT

public:
    explicit book(QWidget *parent=nullptr, int id=-1);

    // to help removing
    int id;

    // update positon
    void move(double add_rate);

    // avoiding malfunction caused by clicking a fading book
    bool deleted;

    void deleteEvent();
    void clickEvent();

private:
    double x1, x2, a;
    // y = -a(x - x1)(x - x2) from x1 to x2
    double v;
    // speed
    int dir;
    // orientation
    double my_time;
    // begin time

    int now_x, now_y; // current position

signals:
    void fallen();
    void myClicked(int id);
};
