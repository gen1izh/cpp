#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_algorithms[NO_ALGO] = "";
    m_algorithms[SORT_CHARS_BY_DESCENDING] = "Сортировка символов текста по убыванию";
    m_algorithms[REVERS_TEXT] = "Разворот текста";
    m_algorithms[SORT_LINES_BY_ASCENDING] = "Сортировка строк текста по возрастанию";
    m_algorithms[CHARS_STATISTICS] = "Статистика по используемым символам в тексте";

    ui->algoBox->clear();

    ui->algoBox->addItem(m_algorithms[NO_ALGO]);
    ui->algoBox->addItem(m_algorithms[SORT_CHARS_BY_DESCENDING]);
    ui->algoBox->addItem(m_algorithms[REVERS_TEXT]);
    ui->algoBox->addItem(m_algorithms[SORT_LINES_BY_ASCENDING]);
    ui->algoBox->addItem(m_algorithms[CHARS_STATISTICS]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QByteArray MainWindow::createJsonPacket(QString algo, QString text)
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

void MainWindow::parseJsonPacket(QByteArray &bytes, QString &algo, QStringList &text)
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

void MainWindow::on_connectButton_clicked()
{
    m_tcpSocket = new QTcpSocket(this);
    bool ok;

    m_tcpSocket->connectToHost(ui->hostEdit->text(), ui->portEdit->text().toInt(&ok,10));
    connect(m_tcpSocket, SIGNAL(connected()), SLOT(connected()));
    connect(m_tcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(checkError(QAbstractSocket::SocketError))
            );
}

// Обработчик данных с сокета
void MainWindow::readyRead()
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_5);
    for (;;) {
        if (!m_blockSize) {
            if (m_tcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_blockSize;
        }

        if (m_tcpSocket->bytesAvailable() < m_blockSize) {
            break;
        }
        QTime       time;
        QByteArray  packet;
        QString     algo;
        QStringList text;

        in >> time >> packet;

        parseJsonPacket(packet, algo, text);

        ui->logEdit->append(time.toString() + " Server has sended answer - [" + algo + "] text: ");
        for ( int i = 0; i < text.size(); i++ ) {
            ui->logEdit->append(text.at(i));
        }

        m_blockSize = 0;
    }
}


// Ошибки соединения
void MainWindow::checkError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                                 "The remote host is closed." :
                                 err == QAbstractSocket::ConnectionRefusedError ?
                                     "The connection was refused." :
                                     QString(m_tcpSocket->errorString())
                                     );
    ui->logEdit->append(strError);
}

// Отправка сообщения серверу
void MainWindow::sendMessageToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0) << QTime::currentTime() << createJsonPacket(QString("ALGO%1").arg(ui->algoBox->currentIndex()),
                                                                  ui->dataEdit->toPlainText());

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_tcpSocket->write(arrBlock);
    ui->dataEdit->setText("");
}

// Протоколирования факта соединения
void MainWindow::connected()
{
    ui->logEdit->append("[Server]: Client was succesfully connected!");
}

void MainWindow::on_sendButton_clicked()
{
    sendMessageToServer();
}
