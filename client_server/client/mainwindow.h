#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDataStream>
#include <QTime>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QScopedPointer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
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
        REVERS_TEXT,
        SORT_LINES_BY_ASCENDING,
        CHARS_STATISTICS
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /*!
     * \brief Указатель на объект сокета
     */
    QTcpSocket         *m_tcpSocket;
    /*!
     * \brief Инициализация размера блока данных
     * CONFIG += c++11
     */
    quint32             m_blockSize = 0;

    /*!
     * \brief хеш алгоритмов
     * TODO: По уму, чтобы дублирования кода не было, нужно
     * вынести в отдельный файл, доступный и  для клиента и для сервера.
     */
    QHash<int,QString>  m_algorithms;


    /*!
     * \brief Создание Json пакета для сервера
     * \param[in] algo - алгоритм
     * \param[in] text - текст
     * \return
     * TODO: По уму, чтобы дублирования кода не было, нужно
     * вынести в отдельный файл, доступный и  для клиента и для сервера.
     */
    QByteArray createJsonPacket(QString algo, QString text);

    /*!
     * \brief Разбор Json пакета от сервера
     * \param[in] bytes - данные
     * \param[in] algo - алгоритм
     * \param[in] text - текст данных
     * TODO: По уму, чтобы дублирования кода не было, нужно
     * вынести в отдельный файл, доступный и  для клиента и для сервера.
     */
    void parseJsonPacket(QByteArray &bytes, QString &algo, QStringList &text);

private slots:
    /*!
     * \brief Обработчик данных с сокета
     */
    void readyRead();

    /*!
     * \brief Ошибки соединения
     */
    void checkError(QAbstractSocket::SocketError);

    /*!
     * \brief Отправка сообщения серверу
     */
    void sendMessageToServer();

    /*!
     * \brief Протоколирования факта соединения
     */
    void connected();

    /*!
     * \brief Нажатие на кнопку соединения
     */
    void on_connectButton_clicked();

    /*!
     * \brief Нажатие на кнопку отправки данных
     * TODO: Нужно сделать проверки на то что соединение установлено
     */
    void on_sendButton_clicked();
};


#endif // MAINWINDOW_H
