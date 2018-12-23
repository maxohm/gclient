#include "msock.h"

msock::msock(QObject *parent) : QObject(parent)
{
    //sock = new QTcpSocket();
    state = stif+"|"+QString::number(stport)+"|0";
    //
    ticker = new QTimer();
    //connect(ticker,SIGNAL(timeout()),this,SLOT(stmod()));
    //ticker->start(sttime);
}

//msock::msock(int i)
//{
//    sock = new QTcpSocket();
//    state = "127.0.0.1|"+QString::number(stport+i);
//    //
//    ticker = new QTimer();
//    //ticker->start(30000+i);
//}

void msock::stmod(){
    //
    QString s = this->rx();
    //
    QStringList* h = new QStringList(
                s.split("|")
                );
    //
    QString _st;
    switch(h->length()){
    case 4:
        if(this->ticker->isActive())
            return this->tx(this->state+"|9");

        if("5"==h->at(3))
            return this->tx(this->state);

        if("4"==h->at(3)){
            s.replace("|3|4","|3|0");
            this->state_new = s;
            this->cmd();
            return;
        };

        if(0>prules.indexOf(
                    h->at(2)+h->at(3)
                    ))
            return this->tx(this->state+"|8");


        if("2"==h->at(3)){
            this->state_new = s;
            this->cmd();
            s.replace("|1|2","|2|3");
        };

//        _st = pdesc.value(
//                    h->at(3).toInt()
//                    );

//        if (_st.isEmpty() || _st.isNull()){
//            return;
//        };

        this->state_new = s;
        connect(this->ticker, SIGNAL(timeout()), this, SLOT(cmd()));
        this->ticker->start(sttime);
        if("2"!=h->at(3))
            return this->tx(s);

        break;
    default:
        break;
    };
};


void msock::tx(QString s)
{
    if (QTcpSocket::ConnectedState!=this->sock->state()){
        return;
    };
    //
    QByteArray* a;
    QTextCodec* rus = QTextCodec::codecForName("utf8");
    if (s.isEmpty() || s.isNull()){
        a = new QByteArray(
                    rus->fromUnicode(this->state)
                    );
    } else {
        a = new QByteArray(
                    rus->fromUnicode(s)
                    );
    };
    //
    this->sock->write(
                a->data(),
                a->size()
                );
    this->sock->waitForBytesWritten();
}

void msock::cmd(){
    this->ticker->stop();

    if (""!=this->state_new){
        QStringList* h = new QStringList(
                    this->state_new.split("|")
                    );
        //
        if (4!=h->length())
            return;
        //
        switch(prules.indexOf(h->at(2)+h->at(3))){
        case 0: case 1: case 2: case 3:
            this->state = h->at(0)+"|"+h->at(1)+"|"+h->at(3);
            break;
        default:
            return this->tx(this->state+"|8");
            break;
        }
        //
        this->state_new="";
        return this->tx(this->state);
    }
}


QString msock::rx()
{
    QTextCodec* rus = QTextCodec::codecForName("utf8");
    QString s = rus->toUnicode(
                this->sock->readAll()
                );
    qDebug() << s;
    return s;
}
