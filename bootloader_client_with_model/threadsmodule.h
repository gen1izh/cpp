#ifndef AT_THREAD_H
#define AT_THREAD_H

#include <QThread>
#include <QtGui>
#include <QSettings>
#include "log.h"
#include <QDebug>
#include "mainwindow.h"
#include "dataoperations.h"

#include "gresbStrategyRelease.h"
#include "ixxatapiwrapper.h"

//#include "interfacestrategy.h"

#include "ackextractor.h"

enum CmdThreadState{
    kSendCommand,
    kIdleCmd
};

extern volatile CmdThreadState cmdThreadState;

enum DataThreadState{
    kSendDataArray,
    kWaitCompleteOperation,
    kIdleData
};

extern volatile DataThreadState dataThreadState;


enum ReceiverThreadState{
    kReceiveState,
    kIdleReceive
};

extern volatile ReceiverThreadState receiverThreadState;


class senderThread : public QThread {
public:
    senderThread();
    ~senderThread();
    void run();
signals:
    void doIt();
};


class receiverThread : public QThread {
public:
    receiverThread();
    ~receiverThread();
    void run();
};


class createSenderThread : public QThread {
public:
    createSenderThread();
    ~createSenderThread();
    void run();
signals:
    void doIt();
};


extern senderThread         sendCanMsgThread;
extern receiverThread       receiveCanMsgThread;
extern createSenderThread   createSenderCanMsgThread;
extern bool                 prACK;
extern bool                 isDataTypeOfMsg;





#endif // AT_THREAD_H
