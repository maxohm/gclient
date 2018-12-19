#include "gclient.h"
#include "ui_gclient.h"
//
#include <QDate>

gclient::gclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gclient)
{
    ui->setupUi(this);
    //
    sock = new QTcpSocket(this);
    sock->connectToHost("127.0.0.1",2000);


}

gclient::~gclient()
{
    delete ui;
}


void gclient::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();

    int rc = ui->log->rowCount();

    ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    ui->log->setItem(rc,0,t);
    ui->log->resizeColumnsToContents();
}

void gclient::on_pushButton_clicked()
{

}

void gclient::on_pushButton_2_clicked()
{

}

void gclient::on_pushButton_3_clicked()
{

}

void gclient::on_pushButton_4_clicked()
{

}
