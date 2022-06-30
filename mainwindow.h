#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Game *game;

signals:
    void gameStart();
    void OpenRank();
    void tryclose();

private slots:
    void on_pushButton_clicked(); // start game

    void on_pushButton_2_clicked(); // look up rank

    void on_pushButton_3_clicked(); // exit

public slots:
    void die();

    void changecur();

    void resetcur();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
