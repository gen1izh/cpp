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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

    QTcpSocket         *m_tcpSocket;
    quint16             m_blockSize = 0;
    QHash<int,QString>  m_algorithms;

    QByteArray createJsonPacket(QString algo, QString text);

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

    /* Обработчики нажатия кнопок */
    void on_connectButton_clicked();
    void on_sendButton_clicked();
};


#endif // MAINWINDOW_H
