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
#include <QRegularExpression>

class Server : public QObject
{
    Q_OBJECT

    /*!
     * Перечисление кодов алгоритмов
     * TODO: По уму, чтобы дублирования кода не было, нужно
     * вынести в отдельный файл, доступный и  для клиента и для сервера.
     */
    enum {
        NO_ALGO = 0,
        SORT_CHARS_BY_DESCENDING,
        REVERSE_TEXT,
        SORT_LINES_BY_ASCENDING,
        CHARS_STATISTICS
    };

    /*!
     * \brief Указатель на объект сервера
     */
    QTcpServer* m_tcpServer;

    /*!
     * \brief Инициализация размера блока данных
     * CONFIG += c++11
     */
    quint32     m_blockSize = 0;

    /*!
     * \brief Номер порта по умолчанию
     * CONFIG += c++11
     */
    quint32     m_port = 100;

    /*!
     * \brief Создание Json пакета для клиента
     * \param[in] algo - алгоритм
     * \param[in] text - текст
     * \return
     */
    QByteArray createJsonPacket(QString algo, QString text);

    /*!
     * \brief Разбор Json пакета от клиента
     * \param[in] bytes - данные
     * \param[in] algo - алгоритм
     * \param[in] text - текст данных
     */
    void parseJsonPacket(QByteArray &bytes, QString &algo, QStringList &text);

public:
    explicit Server(QObject *parent = 0);
    ~Server();

    /*!
     * \brief Запуск сервера
     */
    void start();

    /*!
     * \brief Останов сервера
     */
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
    quint32 blockSize() const;

    /*!
     * \brief Установка размера блока
     * \param[in] blockSize - размер блока
     */
    void setBlockSize(const quint32 &blockSize);

private:

    /*!
     * \brief Отправка сообщения клиенту
     * \param[in] socket - сокет
     * \param[in] str -  строка которую нужно отправить
     */
    void sendMessage(QTcpSocket* socket, const QByteArray &str);

    /*!
     * \brief Выполнить алгоритм
     * \param[in] alg - алгоритм
     * \param[in] text - текст
     * \return
     */
    QStringList execAlgorithm(QString alg, QStringList text);


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
