#ifndef GCLIENT_H
#define GCLIENT_H
//
#include "msock.h"
//
#include <QMainWindow>
#include <QTcpSocket>

namespace Ui {
class gclient;
}

class gclient : public QMainWindow
{
    Q_OBJECT

public:
    explicit gclient(QWidget *parent = 0);
    ~gclient();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    //
    void log(QString s);
    void monitor();
    void rx();
    void tx(QString s);

private:
    Ui::gclient *ui;
    //
    msock* sock;  // Массив сокетов

};

#endif // GCLIENT_H
