#ifndef BOOK_H
#define BOOK_H

#endif // BOOK_H

#include <QPushButton>

class book: public QPushButton
{
    Q_OBJECT

public:
    explicit book(QWidget *parent=nullptr, int id=-1);

    int id;

    // return a bool to show whether has fallen
    void move(double add_rate);

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

//protected:
//    virtual QSize sizeHint() const;
};
