#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QApplication::setOverrideCursor(QCursor(QPixmap(":/cursor/2.cur")));//set mouse shape
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changecur(){
    QApplication::setOverrideCursor(QCursor(QPixmap(":/cursor/3.cur")));
}//Mouse shape change

void MainWindow::resetcur(){
    QApplication::setOverrideCursor(QCursor(QPixmap(":/cursor/2.cur")));
}//Mouse shape Recovery

void MainWindow::on_pushButton_clicked()
{
    hide();
    emit gameStart();
}


void MainWindow::on_pushButton_2_clicked()
{
    hide();
    emit OpenRank();
}


void MainWindow::on_pushButton_3_clicked()
{
    emit tryclose();
}

void MainWindow::die(){
    close();
}
