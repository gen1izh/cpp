#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QHash>
#include <QStringList>

class Message{
public:
  Message();
  QString st;
  int     i;
};

/**
  * Журнал событий
  */
class logger : public QObject {
  Q_OBJECT

  QList<Message>  sysMsgs;
  QList<Message>  protoMsgs;

  public:

    enum {
      SYSTEM_LOGGER=0,
      PROTOCOL_LOGGER
    };

    enum {
      WARNING_MSG_TYPE=0,
      ERROR_MSG_TYPE,
      FATAL_MSG_TYPE,
      INFO_MSG_TYPE,
      DEBUG_MSG_TYPE
    };

    QHash<int, QString> hsTypeMsg;

    explicit logger(QObject *parent = 0);

    void sendDataToViewer( int type, QString msg, int logger );

    void putData( QString msg, int logger );
    void signalReceiveLastMsg( int logger );

    QString getNotViewedMsg( int logger );

  signals:

    void updateSysLogger();
    void updateProtoLogger();

};

#endif // LOGGER_H
