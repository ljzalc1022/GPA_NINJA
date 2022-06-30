#ifndef GAME_H
#define GAME_H

#include <QWidget>

namespace Ui {class Game;}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void show();
    void replay();
    void endEvent();
    void Clicked(int);
    void closeEvent(QCloseEvent *e);
signals:
    void gameStart(Game*);
    void gameEnd();
    void gameClosed();

private:
    Ui::Game *ui;
};

#endif // GAME_H
