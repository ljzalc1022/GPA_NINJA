#include "rank.h"
#include "ui_rank.h"
#include<QDir>
#include<QFile>
#include<bits/stdc++.h>
#include<QTableWidgetItem>
using namespace std;

Rank::Rank(QWidget *parent) : QWidget(parent), ui(new Ui::Rank)
{
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &Rank::rankclose);
}

Rank::~Rank()
{
    delete ui;
}

void Rank::rankclose(){
    emit rankClosed(); close();
}

void Rank::show()
{
    QWidget::show();

    QFile f(QDir::currentPath()+"/grade.txt");                   //qfile operations
    f.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream fin(&f);
    QString str;

    vector<string>v;
    while(!fin.atEnd()){
        str=fin.readLine();
        if(str=="") break;
        v.push_back(str.toStdString());                        //input all the data of scores and time
    }
    sort(v.begin(),v.end(),greater<string>());                 //sort
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(1,200);                    //set the form of QTableWidget
    for(int i=0;i<v.size()&&i<10;++i){
        int num=0;
        for(int j=0;j<10;++j) num=num*10+v[i][j]-'0';          //get int from string
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(to_string(num))));
        string tmp=v[i]; tmp.erase(0,10);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(tmp)));//fill the QTableWidget
    }
    f.close();
}
