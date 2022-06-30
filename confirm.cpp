#include "confirm.h"
#include "ui_confirm.h"
#include<QDir>
#include<QFile>
#include<bits/stdc++.h>
#include<QTableWidgetItem>
using namespace std;

Confirm::Confirm(QWidget *parent) : QWidget(parent), ui(new Ui::Confirm)
{
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,this,&Confirm::closing);//"close" button
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&Confirm::back);//"back" button
}//Interface for dissuasion

Confirm::~Confirm()
{
    delete ui;
}

void Confirm::show()
{
    QWidget::show();
}

void Confirm::closing(){
    emit Closed();//to tell MainWindow to close
    close();
}

void Confirm::back(){
    close();//no matter what the choice is,the confirm window should be closed
}
