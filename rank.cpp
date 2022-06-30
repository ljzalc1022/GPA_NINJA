#include "rank.h"
#include "ui_rank.h"
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
    std::ifstream fin(":/grade/grade.txt");
    char ch[50];
    vector<string>v;
    while(1){
        memset(ch,0,sizeof ch);
        fin.getline(ch,50);
        string s=ch;
        if(s=="") break;
        v.push_back(s);
    }
    sort(v.begin(),v.end(),greater<string>());
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(1,200);
    for(int i=0;i<v.size()&&i<10;++i){
        int num=0;
        for(int j=0;j<10;++j) num=num*10+v[i][j]-'0';
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(to_string(num))));
        string tmp=v[i]; tmp.erase(0,10);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(tmp)));
    }
}
