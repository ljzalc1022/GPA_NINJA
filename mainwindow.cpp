#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <Qpixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setCursor(Qt::PointingHandCursor);
    QApplication::setOverrideCursor(QCursor(QPixmap(":/cursor/Cross.cur")));
}



MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{
    hide();
    emit gameStart();
}


void MainWindow::on_pushButton_2_clicked()
{

}


void MainWindow::on_pushButton_3_clicked()
{
    close();
}

