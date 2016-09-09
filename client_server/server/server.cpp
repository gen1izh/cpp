#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

Server::~Server()
{
    stop();
}

// Создание Json пакета для клиента
QByteArray Server::createJsonPacket(QString algo, QString text)
{
    QStringList Strings = text.split('\n');
    QJsonArray _text;
    _text = QJsonArray::fromStringList(Strings);

    QJsonObject packet;
    packet["algo"] = algo;
    packet["text"] = _text;

    QJsonDocument doc(packet);

    return doc.toJson();
}

// Разбор Json пакета от клиента
void Server::parseJsonPacket(QByteArray &bytes, QString &algo, QStringList &text)
{
    QJsonParseError *err = new QJsonParseError;
    QJsonDocument packet(QJsonDocument::fromJson(bytes, err));

    if(err->error != QJsonParseError::NoError) {
        qDebug() << "Json data error: " << err->errorString();
        return;
    }

    algo = packet.object()["algo"].toString();

    QJsonArray  _text  = packet.object()["text"].toArray();

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
quint32 Server::blockSize() const
{
    return m_blockSize;
}

// Установка размера блока
void Server::setBlockSize(const quint32 &nNextBlockSize)
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

// Останов сервера
void Server::stop()
{
    delete m_tcpServer;
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
            if (clientSocket->bytesAvailable() < sizeof(quint32)) {
                break;
            }
            in >> m_blockSize;
        }

        if (clientSocket->bytesAvailable() < m_blockSize) {
            qDebug() << "Bytes available: " << clientSocket->bytesAvailable();
            qDebug() << "Block size: " << m_blockSize;
            break;
        }

        QTime           time;
        QByteArray      data;
        QString         algo;
        QStringList     text;
        in >> time >> data;

        parseJsonPacket(data, algo, text);

        QString strMessage =
                time.toString() + " " + "Client has sended data - algo[" + algo + "] text:";
        qDebug() << strMessage;

        for ( int i = 0; i < text.size(); i++ ) {
             qDebug() << text.at(i);
        }

        text = execAlgorithm(algo, text);
        QString textWithN="";
        foreach (const QString &str, text) {
            textWithN+=str+"\n";
        }

        m_blockSize = 0;

        sendMessage(clientSocket, createJsonPacket(algo,textWithN));

    }
}

// Отправка сообщения клиенту
void Server::sendMessage(QTcpSocket* socket, const QByteArray& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint32(arrBlock.size() - sizeof(quint32));

    socket->write(arrBlock, arrBlock.size());
}

// Выполнить алгоритм
QStringList Server::execAlgorithm(QString alg, QStringList text)
{
    bool ok;
    int algorithmCode = alg.right(1).toInt(&ok,10);

    QStringList ret;
    QStringList tmp;
    QHash<QString, int> statistic;
    QHashIterator<QString, int> statisticIterator(statistic);

    switch (algorithmCode) {
        case NO_ALGO:

            ret = text;

            break;

        case SORT_CHARS_BY_DESCENDING:

            tmp.clear();
            for (int j = 0; j < text.size(); j++) {
                QString oneString = text.at(j);
                QStringList oneStringList;
                oneStringList.clear();

                for (int i=0; i < oneString.size(); i++) {
                    oneStringList << oneString.at(i);
                }

                // Разбил строку на список строк и отсортировал список строк
                qSort(oneStringList.begin(), oneStringList.end(), qGreater<QString>());

                QString sortedString = "";

                // Затем опять соединил строки в одну строку
                for (int i = 0; i < oneStringList.size(); i++) {
                    sortedString+= oneStringList.at(i);
                }
                tmp.append(sortedString);
            }
            ret = tmp;
            break;

        case REVERSE_TEXT:

            tmp.clear();
            for (int j = 0; j < text.size(); j++) {
                QString oneString = text.at(j);
                QString reverseString="";
                for (int i = 0; i < oneString.size(); i++) {
                    reverseString+= oneString.at(oneString.size()- i-1);
                }

                tmp.append(reverseString);
            }

            ret = tmp;
            break;

        case SORT_LINES_BY_ASCENDING:
            ret = text;
            qSort(ret.begin(), ret.end());

            break;

        case CHARS_STATISTICS:

            tmp.clear();

            // Воспользовался хешем для подсчета статистики.
            for (int i = 0; i < text.size(); i++) {
                QString Stroka = text.at(i);
                for (int j = 0; j < Stroka.size(); j++) {

                    QString _char =  Stroka.at(j);
                    if (statistic.contains(_char)) {
                        statistic[_char] = (++statistic[_char]);
                    }
                    else {
                        statistic[_char] = 1;
                    }
                }
            }

            statisticIterator = statistic;
            while (statisticIterator.hasNext()) {
                statisticIterator.next();
                ret.append(QString("Char: %1 count: %2").arg(statisticIterator.key()).arg(statisticIterator.value()));
            }

            break;

    default:
            break;
    }


    return ret;

}
