#ifndef GRESB_API_H
#define GRESB_API_H

#include <QDebug>

#include "inc/ECI10A.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "ethcan_api.h"
#include "interfaceStrategy.h"

#include <errno.h>
#include <string.h>


#define grip "192.168.0.50"


class ISocketProvider {
    virtual int sendSocket()const=0 ;
    virtual int receiveSocket()const=0;
};


/**
  *  Gresb release
  */
class InitGresb: public IInterfaceInitializationBehavior, public ISocketProvider {
private:
    int                     sock4000,sock4001;
    int                     port;
    struct sockaddr_in      addr;
    int                     len;
    int                     one;
    char                    gresbIp[50];
    unsigned int            baud;

    void init();

public:
    InitGresb() {
        strcpy( gresbIp, grip);
        baud    = 0x807F;
        init();
    }

    int sendSocket() const{
        return sock4000;
    }
    int receiveSocket() const{
        return sock4001;
    }

};

class ReceiveGresb: public IReceiveDataBehavior {
private:
    int                   sock;
    int receive( int interfaceNum, ECI_CTRL_MESSAGE *msg );
public:
    ReceiveGresb(InitGresb *s) {
        sock = s->receiveSocket();
    }


};

class SendGresb: public ISendDataBehavior {
private:
    int                   sock;
    int send( int interfaceNum, ECI_CTRL_MESSAGE *msg, bool isNeedShowMsg );

public:
    SendGresb( InitGresb *s ) {
        sock = s->sendSocket();
    }

};


class CloseGresb: public ICloseBehavior {
  void close() {
    qDebug() << "Close function in gresb does not need to be implemented \n";
  }

};

/**
  * gresb interface
  */
class Gresb : public InterfaceStrategy {
    int                   sock4000,sock4001;
public:

  Gresb() {
      initBehavior    = new InitGresb();
      sendBehavior    = new SendGresb( (InitGresb *)initBehavior );
      receiveBehavior = new ReceiveGresb( (InitGresb *)initBehavior );
      closeBehavior   = new CloseGresb();
  }
  ~Gresb(){}

  void info() {
      qDebug()<<" Gresb interface was choose \n";
  }

};


#endif // GRESB_API_H
