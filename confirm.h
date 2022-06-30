#ifndef CONFIRM_H
#define CONFIRM_H

#include <QWidget>

namespace Ui {class Confirm;}

class Confirm : public QWidget
{
    Q_OBJECT

public:
    explicit Confirm(QWidget *parent = nullptr);
    ~Confirm();

    void show();
    void closing();
    void back();
signals:
    void Closed();
private:
    Ui::Confirm *ui;
};

#endif // RANK_H
