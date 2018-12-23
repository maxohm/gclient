#ifndef MSOCK_H
#define MSOCK_H
//
#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QTextCodec>
//
static const QStringList sstate  = QStringList() << "QAbstractSocket::UnconnectedState" << "QAbstractSocket::HostLookupState" << "QAbstractSocket::ConnectingState" << "QAbstractSocket::ConnectedState" << "QAbstractSocket::BoundState" << "QAbstractSocket::ClosingState" << "QAbstractSocket::ListeningState";
static const QString stif = "127.0.0.1";
static const int stport = 2000;
static const int sttime = 30000;
static const QStringList pdesc = QStringList() << "Не инициализирован" << "Готов к работе" << "Обрабатывает команду" << "Команда обработана";
static const QStringList proto = QStringList() << "NoInit" << "Initialize" << "ExeCommand" << "" << "GetResult" << "GetState";
static const QStringList prules = QStringList() << "01" << "12" << "23" << "30";

//
class msock : public QObject
{
    Q_OBJECT
public:
    explicit msock(QObject *parent = 0);
    virtual ~msock() {};
    //
    QTcpSocket* sock;
    //
    QString state;
    QString state_old;
    QString state_new;
    //
    QTimer* ticker;

signals:

public slots:
    void cmd();
    QString rx();
    void stmod();
    void tx(QString s);

private slots:
//
private:
//

};

#endif // MSOCK_H
