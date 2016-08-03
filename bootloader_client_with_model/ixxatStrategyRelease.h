#ifndef IXXATSTRATEGYRELEASE_H
#define IXXATSTRATEGYRELEASE_H

#include "inc/ECI10A.h"
#include "interfaceStrategy.h"
#include "ixxatapiwrapper.h"

/**
  *  Ixxat wrapper object
  */
extern IXXATApiWrapper            canInterface;

/**
  *  Ixxat release
  */


class InitIxxat: public IInterfaceInitializationBehavior {
public:
   InitIxxat(){
     canInterface._initialization();
     canInterface._open( CAN_INTERFACE0 );
     canInterface._start( CAN_INTERFACE0 );
     canInterface._open( CAN_INTERFACE1 );
     canInterface._start( CAN_INTERFACE1 );
  }
};

class ReceiveIxxat: public IReceiveDataBehavior {
public:
  int receive( int interfaceNum, ECI_CTRL_MESSAGE *msg ) {
      int read_cnt = 0;
      if( ( ECI_OK == canInterface._read( interfaceNum, msg, &read_cnt )) && (read_cnt > 0) ) {
        return 0;
      }
      return -1;
  }
};

class SendIxxat: public ISendDataBehavior {
    public:
  int send( int interfaceNum, ECI_CTRL_MESSAGE *msg, bool isNeedShowMsg ){
    return canInterface._write( interfaceNum, *msg, (int)isNeedShowMsg );
  }
};

class CloseIxxat: public ICloseBehavior {
  void close(){
      canInterface._close( CAN_INTERFACE0 );
      canInterface._close( CAN_INTERFACE1 );
  }
};

/**
  *  Two interface was wrapped in it classes. User is it classes.
  */

/**
  * Ixxat interface
  */
class Ixxat : public InterfaceStrategy {

public:
  Ixxat() {
    initBehavior    = new InitIxxat();
    sendBehavior    = new SendIxxat();
    receiveBehavior = new ReceiveIxxat();
    closeBehavior   = new CloseIxxat();
  }
  ~Ixxat(){}

  void info() {
      qDebug()<<" Ixxat interface was choose \n";
  }
};


#endif // IXXATSTRATEGYRELEASE_H
