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

    // overriding show to emit gameStart signal
    void show();

    void replay();

    void Clicked(int);

    void endEvent();
    void closeEvent(QCloseEvent *e);
signals:
    void gameStart(Game*); // to play and replay
    void gameEnd();    // one game overs a.k.a one book falls
    void gameClosed(); // the game window being closed

private:
    Ui::Game *ui;
};

#endif // GAME_H
