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
    sock = new msock();
    QStringList* h = new QStringList(
                sock->state.split("|")
                );

    sock->sock->connectToHost(h->at(0),h->at(1).toInt());

    connect(sock->ticker, SIGNAL(timeout()), this, SLOT(monitor()));
    //
    log("gclient::gclient sock->sock->state() = ");
    log(sstate[sock->sock->state()]);

}

gclient::~gclient()
{
    delete ui;
}


void gclient::monitor()
{

    QStringList* h = new QStringList(
                sock->state.split("|")
                );
    //
    if (QTcpSocket::ConnectedState!=sock->sock->state()){
        sock->sock->connectToHost(
                    h->at(0),
                    h->at(1).toInt()
                    );
    };
    //
    sock->state = h->at(0) + "|" + h->at(1) + "|" + sstate[sock->sock->state()];
    log("gclient::gclient sock->state = ");
    log(sock->state);
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

void gclient::on_pushButton_1_clicked()
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
