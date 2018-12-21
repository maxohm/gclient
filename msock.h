#ifndef MSOCK_H
#define MSOCK_H
//
#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QTextCodec>
//
static const QStringList sstate  = QStringList() << "QAbstractSocket::UnconnectedState" << "QAbstractSocket::HostLookupState" << "QAbstractSocket::ConnectingState" << "QAbstractSocket::ConnectedState" << "QAbstractSocket::BoundState" << "QAbstractSocket::ClosingState" << "QAbstractSocket::ListeningState";
static const int stport = 2000;
static const QStringList proto = QStringList() << "GetState" << "Initialize" << "ExeCommand" << "GetResult";
//
class msock : public QObject
{
    Q_OBJECT
public:
    explicit msock(QObject *parent = 0);
    virtual ~msock() {};
    //
    QTcpSocket* sock;
    QString state;
    QTimer* ticker;

signals:

public slots:
    QString rx();
    void cmd();
    void tx(QString s);

private slots:
//
private:
//

};

#endif // MSOCK_H
