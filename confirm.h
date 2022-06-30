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

    void show();//to show the confirming widget
    void closing();//when the user wants to close,execute this function
    void back();//when the user wants to go back,execute this function
signals:
    void Closed();//closed signal,to tell MainWindow to close
private:
    Ui::Confirm *ui;
};

#endif // RANK_H
