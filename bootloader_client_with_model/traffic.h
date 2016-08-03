#ifndef TRAFFIC_H
#define TRAFFIC_H


#include <QList>
#include "inc/ECI10A.h"

//class traffic
//{
//public:
//    traffic();
//};


typedef struct{
    ECI_CTRL_MESSAGE msg;
    bool             show;
}sendMsgArray;

extern QList<sendMsgArray> sendPacksQuery;

#endif // TRAFFIC_H
