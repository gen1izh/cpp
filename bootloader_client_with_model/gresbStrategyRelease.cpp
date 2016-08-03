#include "gresbStrategyRelease.h"


/**
  * Init baudrate gresb
  */
void InitGresb::init()
{
    one = 1;
    addr.sin_family           = AF_INET;
    addr.sin_addr.s_addr      = inet_addr(gresbIp);
    if (addr.sin_addr.s_addr == INADDR_NONE) {
        qDebug() << " Illegal ip address ";
        return;
    }
    addr.sin_port = htons(4000);

    sock4000 = socket(PF_INET, SOCK_STREAM, 0);
    setsockopt(sock4000, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
    if ( connect(sock4000, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0 ) {
        qDebug()<<"connect: ";
        return;
    }
    if (can_setbaud(sock4000, baud) < 0) {
        qDebug()<<"can_setbaud: ";
    }
    else {
        qDebug()<<"Set baud rate to " << baud << "\n";
    }


    sock4001 = socket(AF_INET, SOCK_STREAM, 0);
    if (sock4001 < 0) {
        qDebug()<<"socket";
        return;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(gresbIp);
    if (addr.sin_addr.s_addr == INADDR_NONE) {
        qDebug()<<"Illegal ip address";
        return;
    }
    addr.sin_port = htons(4001);
//    sock = socket(PF_INET, SOCK_STREAM, 0);
    int errnosock;
    errnosock = connect(sock4001, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
    if ( errnosock < 0) {
        qDebug()<<"error connect = " << errno;
        return;
    }


}



/**
  *  Receive gresb realization
  */
int ReceiveGresb::receive(int interfaceNum, ECI_CTRL_MESSAGE *msg)
{
    int                     ff, rtr, dlc, id;
    char                    buf[8];
//    one = 1;



    /**
      * FIXME: For clear warning ( interfaceNum ) not used
      */
    interfaceNum = 0;
    interfaceNum++;

    int len = can_recv(sock, &ff, &rtr, &id, &dlc, (unsigned char*)&buf[0]);
    if (len < 0) {
        qDebug()<<"can_recv";
        return -1;
    }
    else if (len > 0 ) {
        msg->u.sCanMessage.u.V0.uMsgInfo.Bits.dlc    = dlc;
        msg->u.sCanMessage.u.V0.abData[0]            = buf[0];
        msg->u.sCanMessage.u.V0.abData[1]            = buf[1];
        msg->u.sCanMessage.u.V0.abData[2]            = buf[2];
        msg->u.sCanMessage.u.V0.abData[3]            = buf[3];
        msg->u.sCanMessage.u.V0.abData[4]            = buf[4];
        msg->u.sCanMessage.u.V0.abData[5]            = buf[5];
        msg->u.sCanMessage.u.V0.abData[6]            = buf[6];
        msg->u.sCanMessage.u.V0.abData[7]            = buf[7];
        msg->u.sCanMessage.u.V0.dwMsgId              = id;
    }

    return 0;
}

/**
  * Send gresb realization
  */
int SendGresb::send(int interfaceNum, ECI_CTRL_MESSAGE *msg, bool isNeedShowMsg )
{
    int             n;
//    int             len;
    /**
      * FIXME: For clear warning ( interfaceNum, isNeedShowMsg) not used
      */
    interfaceNum = 0;
    interfaceNum++;
    isNeedShowMsg = 0;
    isNeedShowMsg++;

//    if (len > 0) {
        if ( (n = can_send(sock, 1, 0, msg->u.sCanMessage.u.V0.dwMsgId, msg->u.sCanMessage.u.V0.uMsgInfo.Bits.dlc,  msg->u.sCanMessage.u.V0.abData)) < 0) {
            qDebug()<<"Error writing socket: ";
            return -1;
        } else if (n == 0) {
            qDebug()<<"Remote side closed connection";
        }
//    }
    return 0;
}
