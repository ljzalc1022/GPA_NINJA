#ifndef BOOK_H
#define BOOK_H

#endif // BOOK_H

#include <QWidget>

class book: public QWidget
{
    Q_OBJECT

public:
    explicit book(QWidget *parent=nullptr);
    ~book();

private:
    double x1, x2, a;
    // y = a(x - x1)(x - x2) from x1 to x2
    double v;
    // speed
};
