#ifndef PRTANSWEREXTRACTOR_H
#define PRTANSWEREXTRACTOR_H

#include "ixxatapiwrapper.h"
#include <QStringList>

#include "threadsmodule.h"
#include "mainwindow.h"
#include "log.h"
#include <QDebug>
#include <QTime>
#include <QMutex>
#include "model.h"
#include "traffic.h"



#define PROTO_OP_ENTER_BOOTLOADER                   0x0D
#define PROTO_OP_WRITE                              0x08
#define PROTO_OP_ERASE_AND_WRITE                    0x07
#define PROTO_OP_SET_ACTIVE_IMAGE                   0x11
#define PROTO_OP_LOAD_IMAGE                         0x0A
#define PROTO_OP_VERIFY_IMAGE                       0x09
#define PROTO_OP_ERASE_AREA                         0x0F

#define PROTO_OP_TELEMETRY                          0xFF


#define SENDER_ADDR                                 0x20
#define RECEIVER_ADDR                               0x0A

//#define B7                                          0x1
//#define B6                                          0x1
//#define B5                                          0x1
//#define B4                                          0x1


class AckExtractor {
public:
    QList<QStringList> oneRecord;

    AckExtractor();
    ~AckExtractor();
    void _routePacket( sendMsgArray msg );
    void oneRecordFill( sendMsgArray msg );
private:
    void _extractAck(ECI_CTRL_MESSAGE msg);
    void _extractTelemetry(ECI_CTRL_MESSAGE msg);

};

extern AckExtractor         dataExtractor;

extern int                  lastCommand;
#endif // PRTANSWEREXTRACTOR_H
