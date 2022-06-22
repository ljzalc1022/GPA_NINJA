#ifndef BOOK_CONTROLLER_H
#define BOOK_CONTROLLER_H

#endif // BOOK_CONTROLLER_H

#include "book.h"

#include <QThread>

class book_controller: public QThread
{
    Q_OBJECT

public:
    explicit book_controller(QObject *parent=nullptr, book* entity=nullptr);
    ~book_controller();

protected:
    void run();

private:
    book* entity;
};
