#include "msock.h"

msock::msock(QObject *parent) : QObject(parent)
{
    sock = new QTcpSocket();
    state = "127.0.0.1|"+QString::number(stport);
    //
    ticker = new QTimer();
    ticker->start(30000);
}

//msock::msock(int i)
//{
//    sock = new QTcpSocket();
//    state = "127.0.0.1|"+QString::number(stport+i);
//    //
//    ticker = new QTimer();
//    //ticker->start(30000+i);
//}

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
    //
    this->sock->waitForBytesWritten();
}

void msock::cmd(){
    if (QTcpSocket::ConnectedState!=this->sock->state()){
        return;
    };
    //
    QTextCodec* rus = QTextCodec::codecForName("utf8");
    QString s = rus->toUnicode(
                this->sock->readAll()
                );
    //
    if(0>proto.indexOf(s)){
        tx("ERR_COMMAND_UNKNOWN "+s);
        return;
    };
    switch(proto.indexOf(s)){
    case 0:
        tx(state+"|GetState");
        break;
    case 1:
        tx(state+"|Initialize");
        break;
    case 2:
        tx(state+"|ExeCommand");
        break;
    case 3:
        tx(state+"|GetResult");
        break;
    default:
        tx("ERR_COMMAND_UNKNOWN "+s);
        break;
    };
}

QString msock::rx()
{
    QTextCodec* rus = QTextCodec::codecForName("utf8");
    return rus->toUnicode(
                this->sock->readAll()
                );
}






