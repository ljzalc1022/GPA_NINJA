#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    QObject::connect(this, &Game::gameStart, [=](){
        this->ui->verticalWidget->hide();
    });

    QObject::connect(this, &Game::gameEnd, this, &Game::endEvent);
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &Game::replay);
}

Game::~Game()
{
    delete ui;
}

void Game::show()
{
    QWidget::show();
    emit gameStart(this);
}

void Game::replay()
{
    emit gameStart(this);
}

void Game::endEvent()
{
    ui->verticalWidget->show();
}

void Game::closeEvent(QCloseEvent *e) {
    emit gameClosed();
}
