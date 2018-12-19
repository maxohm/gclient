#include "gclient.h"
#include "ui_gclient.h"

gclient::gclient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gclient)
{
    ui->setupUi(this);
}

gclient::~gclient()
{
    delete ui;
}

void gclient::on_pushButton_clicked()
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
