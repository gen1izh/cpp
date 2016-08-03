#ifndef INTERFACESTRATEGY_H
#define INTERFACESTRATEGY_H

#include <QDebug>
#include "inc/ECI10A.h"


/**
  * Init interface
  */
class IInterfaceInitializationBehavior{
public :
  virtual void init(){}
};

/**
  * Receive interface
  */
class IReceiveDataBehavior{
public :
  virtual int receive( int interfaceNum, ECI_CTRL_MESSAGE *msg )=0;
};

/**
  * Send interface
  */
class ISendDataBehavior{
public :
  virtual int send( int interfaceNum, ECI_CTRL_MESSAGE *msg, bool isNeedShowMsg )=0;
};

/**
  * Close interface
  */
class ICloseBehavior{
public :
  virtual void close(){}
};


/**
  * Base class which include all interfaces(term from C++ oop, not hw)
  * It some bridge for user and concrete realeazation api.
  */

/**
  * Strategy interface
  */
class InterfaceStrategy
{
public:
    InterfaceStrategy(){}
    virtual ~InterfaceStrategy(){}

    IInterfaceInitializationBehavior      *initBehavior;
    IReceiveDataBehavior                  *receiveBehavior;
    ISendDataBehavior                     *sendBehavior;
    ICloseBehavior                        *closeBehavior;

    virtual void performInit() {
        initBehavior->init();
    }


    virtual int performReceive( int interfaceNum, ECI_CTRL_MESSAGE *msg ) {
        return receiveBehavior->receive( interfaceNum, msg );
    }


    virtual int performSend( int interfaceNum, ECI_CTRL_MESSAGE *msg, bool isNeedShowMsg ) {
        return sendBehavior->send( interfaceNum, msg, isNeedShowMsg );
    }

    virtual void performClose() {
        closeBehavior->close();
    }

    virtual void display(){}
};

extern InterfaceStrategy *InteractInterface;

#endif // INTERFACESTRATEGY_H
