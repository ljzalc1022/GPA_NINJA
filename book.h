#ifndef BOOK_H
#define BOOK_H

#endif // BOOK_H

#include <QPushButton>

class book: public QPushButton
{
    Q_OBJECT

public:
    explicit book(QWidget *parent=nullptr);

    // return a bool to show whether has fallen
    bool cal_pos(double &x, double &y, int timer);

    bool deleted;
    void deleteEvent();

private:
    double x1, x2, a;
    // y = -a(x - x1)(x - x2) from x1 to x2
    double v;
    // speed
    int dir;
    // orientation

signals:
    void fallen();

protected:
    virtual QSize sizeHint() const;
};
