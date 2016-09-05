#include <QCoreApplication>
#include <QThread>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server *serv = new Server();
    qDebug() << "Server class initialized";
    serv->setPort(100);
    qDebug() << "Server port installed";
    serv->start();
    qDebug() << "Server listen started";
    int code = a.exec();

    serv->deleteLater();

    return code;
}

