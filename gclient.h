#ifndef GCLIENT_H
#define GCLIENT_H

#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::gclient *ui;
    //
#ifdef HAVE_QT5
    QMap<int, QString> states;		// Массив параметров хостов для обмена
    QMap<int, QTcpSocket*> socket;  // Массив сокетов
#endif

};

#endif // GCLIENT_H
