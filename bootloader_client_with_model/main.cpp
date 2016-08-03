#include <QtGui/QApplication>
#include "mainwindow.h"
#include "ixxatapiwrapper.h"
#include "threadsmodule.h"
#include "interfaceStrategy.h"
#include "ixxatStrategyRelease.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();


    /**
      * Choose interface by transmite data
      */
    InteractInterface = new Ixxat();

    w.setViewForm();

    /**
      * Initialization of states threads
      */
    cmdThreadState          = kIdleCmd;
    dataThreadState         = kIdleData;
    receiverThreadState     = kReceiveState;

    /**
      * Start Receiver thread
      */
    receiveCanMsgThread.start();

    /**
      * Start Sender thread
      */
    sendCanMsgThread.start();

    /**
      * Start data arrays creator thread
      */
    createSenderCanMsgThread.start();

    return a.exec();
}
