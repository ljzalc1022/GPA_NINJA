#include "book.h"

const int WIDTH = 1000;
const int HEIGHT = 600;

book::book(QWidget *parent) : QWidget(parent)
{
    x1 = rand() % WIDTH;
    x2 = rand() % WIDTH;
    a = rand() % HEIGHT;
    if(x1 == x2) {
        if(x1 == 0) ++x2;
        else --x1;
    }

    // total on-screen time could be 1s, 1.5s or 3s
    v = (x2 - x1) * (double(rand() % 3 + 1) / 3);
    v /= 1000;

    // size of book
    setFixedSize(50, 50);
}
