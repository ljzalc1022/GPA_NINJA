#include "game.h"
#include "ui_game.h"
#include<bits/stdc++.h>

Game::Game(QWidget *parent) : QWidget(parent), ui(new Ui::Game)
{
    ui->setupUi(this);
    QObject::connect(this, &Game::gameStart, [=](){
        this->ui->verticalWidget->hide();
    }); // hide game-over when it's not

    QObject::connect(this, &Game::gameEnd, this, &Game::endEvent);

    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &Game::replay); // replay button
}//Main body of the game

Game::~Game()
{
    delete ui;
}

void Game::show()//initial show of the counter
{
    QWidget::show();
    emit gameStart(this);
    ui->textBrowser_2->setCurrentFont(QFont("Microsoft YaHei UI",18));
    ui->textBrowser_2->setText(QString::fromStdString("准备好！"));
    ui->textBrowser_2->setCurrentFont(QFont("Microsoft YaHei UI",18));
}

int number;
void Game::Clicked(int id)//when click,add the number for the counter
{
    ++number;
    ui->textBrowser_2->setCurrentFont(QFont("Microsoft YaHei UI",18));
    ui->textBrowser_2->setText(QString::fromStdString("已修: "+std::to_string(number)+"门课"));
    ui->textBrowser_2->setCurrentFont(QFont("Microsoft YaHei UI",18));
}

void Game::replay()
{
    number=0;
    emit gameStart(this);
}

void Game::endEvent()//when end,set the number to zero
{
    number=0;
    ui->textBrowser_2->setCurrentFont(QFont("Microsoft YaHei UI",18));
    ui->textBrowser_2->setText(QString::fromStdString("寄！"));
    ui->textBrowser_2->setCurrentFont(QFont("Microsoft YaHei UI",18));
    ui->verticalWidget->show();
}

void Game::closeEvent(QCloseEvent *e) {
    number=0;
    emit gameClosed();
}
