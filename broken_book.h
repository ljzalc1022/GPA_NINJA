#ifndef BROKEN_BOOK_H
#define BROKEN_BOOK_H

#endif // BROKEN_BOOK_H

#include <QPushButton>

class broken_book: public QPushButton
{
    Q_OBJECT

public:
    explicit broken_book(QWidget *parent=nullptr);

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

signals:
    void fallen();
    void myClicked(int id);

protected:
    virtual QSize sizeHint() const;
};
