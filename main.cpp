#include "gclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gclient w;
    w.show();

    return a.exec();
}
