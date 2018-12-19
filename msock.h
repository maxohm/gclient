#ifndef MSOCK_H
#define MSOCK_H
//
#include <QTimer>
#include <QTcpSocket>
//
static const QStringList sstate  = QStringList() << "QAbstractSocket::UnconnectedState" << "QAbstractSocket::HostLookupState" << "QAbstractSocket::ConnectingState" << "QAbstractSocket::ConnectedState" << "QAbstractSocket::BoundState" << "QAbstractSocket::ClosingState" << "QAbstractSocket::ListeningState";
static const int stport = 2000;
//

class msock
{
public:
    msock();
    msock(int i);
    //
    QTcpSocket* sock;
    QString state;
    QTimer* ticker;

private slots:

private:


};

#endif // MSOCK_H
