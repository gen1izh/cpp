#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtAlgorithms>

class Server : public QObject
{
    Q_OBJECT

    enum {
        NO_ALGO = 0,
        SORT_CHARS_BY_DESCENDING,
        REVERSE_TEXT,
        SORT_LINES_BY_ASCENDING,
        CHARS_STATISTICS
    };

    QTcpServer* m_tcpServer;
    quint16     m_blockSize = 0;
    quint32     m_port = 100;

    QByteArray createJsonPacket(QString algo, QString text);

    void parseJsonPacket(QByteArray &bytes, QString &algo, QStringList &text);

public:
    explicit Server(QObject *parent = 0);
    ~Server() {
        stop();
    }

    // Запуск сервера
    void start();

    // Останов сервера
    void stop();

    /*!
     * \brief Чтение порта
     * \return номер порта
     */
    quint32 port() const;

    /*!
     * \brief Установка порта
     * \param[in] port - номер порта
     */
    void setPort(const quint32 &port);

    /*!
     * \brief Чтение размера блока
     * \return  размер блока
     */
    quint16 blockSize() const;

    /*!
     * \brief Установка размера блока
     * \param[in] blockSize - размер блока
     */
    void setBlockSize(const quint16 &blockSize);

private:
    /*!
     * \brief Отправка сообщения клиенту
     * \param[in] socket - сокет
     * \param[in] str -  строка которую нужно отправить
     */
    void sendMessage(QTcpSocket* socket, const QByteArray &str);

    QStringList execAlgorithm(QString alg, QStringList text);

    bool caseInsensitiveLessThan(const QString &s1, const QString &s2);
public slots:

    /*!
     * \brief Слот вызывается при каждом новом подключении нового пользователя
     */
     void newConnect();

    /*!
     * \brief Вызывается каждый раз при соединении с новым клиентом
     */
    void readClient();
};


#endif // SERVER_H
