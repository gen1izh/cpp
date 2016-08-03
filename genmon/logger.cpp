#include "logger.h"
#include <QDebug>

logger::logger(QObject *parent):
  QObject(parent) {
  hsTypeMsg[WARNING_MSG_TYPE] = "<font color='maroon'><b>[WARN]</b></font>";
  hsTypeMsg[ERROR_MSG_TYPE]   = "<font color='brown'><b>[ERR]</b></font>";
  hsTypeMsg[FATAL_MSG_TYPE]   = "<font color='red'><b>[FATAL]</b></font>";
  hsTypeMsg[INFO_MSG_TYPE]    = "<font color='blue'><b>[INFO]</b></font>";
  hsTypeMsg[DEBUG_MSG_TYPE]   = "<font color='green'><b>[DEBUG]</b></font>";
}

/**
  * «апись сообщени€ в лог
  */
void logger::putData( QString msg, int logger ) {
  Message m;
  m.st = msg;
  m.i  = 0;
  if ( logger == SYSTEM_LOGGER ) {
    sysMsgs.append( m );
  }
  else if( logger == PROTOCOL_LOGGER ) {
    protoMsgs.append( m );
  }
}

/**
  * ¬ывод последнего собщени€ по событию
  */
void logger::signalReceiveLastMsg( int logger ) {

  if ( logger == SYSTEM_LOGGER ) {
    emit updateSysLogger();
  }
  else if( logger == PROTOCOL_LOGGER ) {
    emit updateProtoLogger();
  }
}

/**
  * ¬ывод последнего собщени€ по событию на представление
  */
void logger::sendDataToViewer( int type, QString msg, int logger ) {
  if ( logger == SYSTEM_LOGGER ) {
    putData( QString("%1  %2").arg(hsTypeMsg[type]).arg(msg), logger );
  }
  else {
    putData( QString("%1").arg(msg), logger );
  }

  signalReceiveLastMsg( logger );
}


QString logger::getNotViewedMsg(int logger) {

  QString endFlag = "endSearchByLogger";

  if ( logger == SYSTEM_LOGGER ) {
    for ( int i = 0; i < sysMsgs.size(); i++ ) {
      if ( sysMsgs.at(i).i == 0 ){
        sysMsgs[i].i = 1;
        return sysMsgs.at(i).st;
      }
    }
  }
  else if( logger == PROTOCOL_LOGGER ) {
    for ( int i = 0; i < protoMsgs.size(); i++ ) {
      if ( protoMsgs.at(i).i == 0 ){
        protoMsgs[i].i = 1;
        return protoMsgs.at(i).st;
      }
    }
  }

  return endFlag;
}

Message::Message()
{
}

