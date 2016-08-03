#ifndef LOG_H
#define LOG_H
#include <QString>
#include <QList>
#include <QObject>

class CommandLogger : public QObject {
    Q_OBJECT
public:
    QList<QString> _log;
    explicit CommandLogger(QObject *parent = 0);
    void refresh();
    void add(QString str);
    void clear();
signals:
    void doIt();
};


class ProgressSendingData : public QObject {
    Q_OBJECT
public:
    explicit ProgressSendingData(QObject *parent = 0);
    void refresh();
signals:
    void doIt();
};


extern CommandLogger cmdLog;
extern CommandLogger telemetryLog;
extern ProgressSendingData sPacketsBar;

#endif // LOG_H
