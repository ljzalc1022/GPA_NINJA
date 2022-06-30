#ifndef RANK_H
#define RANK_H

#include <QWidget>

namespace Ui {class Rank;}

class Rank : public QWidget
{
    Q_OBJECT

public:
    explicit Rank(QWidget *parent = nullptr);
    ~Rank();

    void show();
    void rankclose();

signals:
    void rankClosed();

private:
    Ui::Rank *ui;
};

#endif // RANK_H
