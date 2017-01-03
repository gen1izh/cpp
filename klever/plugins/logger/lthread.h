#ifndef LTHREAD_H
#define LTHREAD_H

#include <QThread>
#include <interfaces/ilogger.h>

struct logPacket {
    QObject *ptr;
    QString datetime;
    QString txt;
    MessagesTypes type;
};

class LThread : public QThread {
    Q_OBJECT

     void run();

public:
    LThread();

    /*
     * Забрать сообщение из списка сообщений
     */
    logPacket takeItemFromlogList() {
        return m_logList.takeFirst();
    }

    /*
     * Добавить сообщение в списко сообщений
     */
    void appendItemToLogList(const logPacket &item) {
        m_logList.append(item);
    }

protected:

    /*
     * Список сообщений
     */
    QList<logPacket> m_logList;

signals:
    void sendMessage(const QString &txt);
};

#endif // LTHREAD_H
