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

    void show();//to show the rank list
    void rankclose();//to hide rank list and tell MainWindow to show again

signals:
    void rankClosed();//closed signal,to tell MainWindow to show

private:
    Ui::Rank *ui;
};

#endif // RANK_H
