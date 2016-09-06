#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

QByteArray Server::createJsonPacket(QString algo, QString text)
{
    QJsonArray packet;

    QJsonObject _algo;
    _algo["algo"] = algo;

    packet.append(_algo);

    QStringList strList = text.split('\n');

    QJsonArray _text;

    _text.fromStringList(strList);

    packet.append(_text);

    QJsonDocument doc(packet);

    return doc.toJson();
}

void Server::parseJsonPacket(QByteArray &bytes, QString &algo, QStringList &text)
{
    QJsonParseError *err = new QJsonParseError;
    QJsonDocument packet(QJsonDocument::fromJson(bytes, err));

    if(err->error != QJsonParseError::NoError) {
        qDebug() << "Json data error: " << err->errorString();
        return;
    }

    QJsonObject _algo  = packet.array().at(0)["algo"];

    QJsonArray  _text  = packet.array().at(1);

    algo = _algo["algo"].toString();

    text.clear();

    for (int i = 0; i < _text.size(); i++) {
        text.append(_text.at(i).toString());
    }

}


// Чтение порта
quint32 Server::port() const
{
    return m_port;
}

// Установка порта
void Server::setPort(const quint32 &port)
{
    m_port = port;
}

// Чтение размера блока
quint16 Server::blockSize() const
{
    return m_blockSize;
}

// Установка размера блока
void Server::setBlockSize(const quint16 &nNextBlockSize)
{
    m_blockSize = nNextBlockSize;
}

// Запуск сервера
void Server::start()
{
    m_tcpServer = new QTcpServer(this);
    if (!m_tcpServer->listen(QHostAddress::Any, port())) {
        qDebug() <<   "Unable to start the server: " + m_tcpServer->errorString();
        m_tcpServer->close();
        return;
    }
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(newConnect()));
}

void Server::stop()
{
    m_tcpServer->deleteLater();
}

// Слот вызывается при каждом новом подключении нового пользователя
void Server::newConnect()
{
    QTcpSocket* clientSocket = m_tcpServer->nextPendingConnection();

    // disconnected - отсоединение клиента
    // readyRead - готовность клиента к передачи данных
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readClient()));

//    sendMessage(clientSocket, "[Server]: Client was succesfully connected!");
}

// Вызывается каждый раз при соединении с новым клиентом
void Server::readClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_5);
    for (;;) {
        if (!m_blockSize) {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_blockSize;
        }

        if (clientSocket->bytesAvailable() < m_blockSize) {
            break;
        }
        QTime           time;
        QByteArray      data;
        QString         algo, text;
        in >> time >> data;

        parseJsonPacket(data, algo, text);

        QString strMessage =
                time.toString() + " " + "Client has sended - algo[" + algo + "] text["+text+"]";
        qDebug() << strMessage;

        text = execAlgorithm(algo, text);

        m_blockSize = 0;

        sendMessage(clientSocket, createJsonPacket(algo,text));
    }
}

// Отправка сообщения клиенту
void Server::sendMessage(QTcpSocket* socket, const QByteArray& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    socket->write(arrBlock);
}

QString Server::execAlgorithm(QString alg, QString text)
{
    bool ok;
    int algorithmCode = alg.right(1).toInt(&ok,10);

    QString ret;
    QString tmp;

    switch (algorithmCode) {
        case NO_ALGO:
            ret = text;
            break;

        case SORT_CHARS_BY_DESCENDING:
            ret = text;
            break;

        case REVERSE_TEXT:

            tmp.clear();

            for (int i = 0; i < text.size(); i++) {
                tmp+= text.at(text.size()- i-1);
            }

            ret = tmp;
            break;

        case SORT_LINES_BY_ASCENDING:
            ret = text;
            break;

        case CHARS_STATISTICS:
            ret = text;
            break;

        default:
            break;
    }


    return ret;

}