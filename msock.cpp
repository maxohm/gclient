#include "msock.h"

msock::msock()
{
    sock = new QTcpSocket();
    state = "127.0.0.1|"+QString::number(stport);
    //
    ticker = new QTimer();
    ticker->start(30000);
}

msock::msock(int i)
{
    sock = new QTcpSocket();
    state = "127.0.0.1|"+QString::number(stport+i);
    //
    ticker = new QTimer();
    //ticker->start(30000+i);
}
