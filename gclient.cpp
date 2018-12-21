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

    sock->sock->connectToHost(
                h->at(0),
                h->at(1).toInt()
                );

    connect(sock->ticker, SIGNAL(timeout()), this, SLOT(monitor()));
    //connect(socket[j], SIGNAL(connected()), SLOT(slotConnected()));
    connect(sock->sock, SIGNAL(readyRead()), this, SLOT(rx()));
    //
    log("gclient::gclient sock->sock->state() = ");
    log(QString::number(sock->sock->state()));
    //log(sstate[sock->sock->state()]);
}

gclient::~gclient()
{
    delete ui;
}

void gclient::tx(QString s)
{
    if (QTcpSocket::ConnectedState!=sock->sock->state())
        return;
    //
    sock->tx(sock->state);
}

void gclient::rx()
{
    QString s = sock->rx();
    log("gclient::rx() "+s+" state "+QString::number(sock->sock->state()));
    this->sock->state = s;
}

void gclient::monitor()
{
    QStringList* h = new QStringList(
                sock->state.split("|")
                );
    if(2>h->length())
        return;
    //
    if (QTcpSocket::ConnectedState!=sock->sock->state()){
        sock->sock->connectToHost(
                    h->at(0),
                    h->at(1).toInt()
                    );

    } else {
        this->setWindowTitle("GCLIENT "+h->at(0)+":"+h->at(1));
    };
    //
    sock->state = h->at(0) + "|" + h->at(1) + "|" + QString::number(sock->sock->state());
    log("gclient::gclient sock->state = ");
    log(sock->state);
    //

}

void gclient::log(QString s)
{
    QDate d = QDate::currentDate();
    QTime c = QTime::currentTime();
    //
    int rc = ui->log->rowCount();
    //
    ui->log->insertRow(rc);
    QTableWidgetItem *t= new QTableWidgetItem (d.toString("dd.MM.yy")+" "+c.toString("hh:mm:ss")+" "+s);
    ui->log->setItem(rc,0,t);
    ui->log->resizeColumnsToContents();
}

void gclient::on_pushButton_1_clicked()
{
    sock->tx("Initialize");
}

void gclient::on_pushButton_2_clicked()
{

    sock->tx("ExeCommand");
}

void gclient::on_pushButton_3_clicked()
{
    sock->tx("fufufufu");
}

void gclient::on_pushButton_4_clicked()
{
    sock->tx("GetState");
}
