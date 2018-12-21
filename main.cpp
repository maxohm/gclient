#include "gclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTextCodec* rus = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(rus);
    //
    QApplication a(argc, argv);
    gclient w;
    w.show();
    //
    return a.exec();
}
