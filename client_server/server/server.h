#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>

class Server : public QObject
{
    Q_OBJECT

    QTcpServer* m_tcpServer;
    quint16     m_nNextBlockSize = 0;

    quint32     m_port;

public:
    explicit Server(QObject *parent = 0);
    ~Server() {
        m_tcpServer->deleteLater();
    }

    void start();


    quint32 port() const;
    void setPort(const quint32 &port);

signals:

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};


#endif // SERVER_H
