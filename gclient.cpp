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
    sock->sock = new QTcpSocket();
    QStringList* h = new QStringList(
                sock->state.split("|")
                );
    sock->sock->connectToHost(
                h->at(0),
                h->at(1).toInt()
                );
    //connect(sock->ticker, SIGNAL(timeout()), this, SLOT(monitor()));
    connect(sock->sock, SIGNAL(readyRead()), this, SLOT(rx()));
    connect(this->ui->log->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), this->ui->log, SLOT(scrollToBottom()));
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
    //log("gclient::rx() received "+s);
    //
    QStringList* h = new QStringList(
                s.split("|")
                );
    QString _st;
    switch(h->length()){
    case 3:
        _st = pdesc.value(
                    h->at(2).toInt()
                    );

        if (_st.isEmpty() || _st.isNull()){
            log("Клиент получил ошибочные данные. Обработка прервана.");
            return;
        };

        this->setWindowTitle("GCLIENT ID "+h->at(1));
        log("Клиент ID ["+h->at(1)+"] состояние ["+_st+"]");
        sock->state = s;

        break;
    case 4:
        if ("9"==h->at(3))
            return log("Ожидание изменения состояния клиента ["+h->at(1)+"]");

        if ("8"==h->at(3)){
            log("Смена состояния клиента ["+h->at(1)+"] на запрошенное ");
            return log("не возможна из состояния ["+pdesc.value(
                    h->at(2).toInt()
                    )+"]");
        };

        _st = pdesc.value(
                    h->at(3).toInt()
                    );

        if (_st.isEmpty() || _st.isNull()){
            log("Клиент получил ошибочные данные. Обработка прервана.");
            return;
        };

        log("Запрос на изменение состояния клиента ["+h->at(1)+"] принят");

        break;
    default:
        log("Клиент получил ошибочные данные. Обработка прервана.");
        break;
    }
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
    sock->tx(this->sock->state+"|"+QString::number(
                   proto.indexOf("Initialize")
                 )
             );
}

void gclient::on_pushButton_2_clicked()
{
    sock->tx(this->sock->state+"|"+QString::number(
                   proto.indexOf("ExeCommand")
                 )
             );
}

void gclient::on_pushButton_3_clicked()
{
    sock->tx(this->sock->state+"|"+QString::number(
                   proto.indexOf("GetResult")
                 )
             );
}

void gclient::on_pushButton_4_clicked()
{
    sock->tx(this->sock->state+"|"+QString::number(
                   proto.indexOf("GetState")
                 )
             );
}
