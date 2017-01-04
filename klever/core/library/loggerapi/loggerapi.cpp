#include "loggerapi.h"

#include <QDateTime>
#include <interfaces/ilogger.h>
#include <frameWork/base.h>

// Журналирование информационного сообщения
void Library::LoggerApi::logInfo(QObject *ptr, QString txt)
{
    QString datetime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz dd.MM.yyyy");
    ILoggerPlugin *loggerPtr = static_cast<ILoggerPlugin*>(Core::Plugins::instance().plugins()["logger"]);
    if (loggerPtr != NULL) {
        loggerPtr->log(ptr, datetime, txt, MESSAGE_INFO);
    }
}

// Журналирование сообщения предупреждения
void Library::LoggerApi::logWarning(QObject *ptr, QString txt) {
    QString datetime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz dd.MM.yyyy");
    ILoggerPlugin *loggerPtr = static_cast<ILoggerPlugin*>(Core::Plugins::instance().plugins()["logger"]);
    if (loggerPtr != NULL) {
        loggerPtr->log(ptr, datetime, txt, MESSAGE_WARNING);
    }
}

// Журналирование сообщения с ошибкой
void Library::LoggerApi::logError(QObject *ptr, QString txt) {
    QString datetime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz dd.MM.yyyy");
    ILoggerPlugin *loggerPtr = static_cast<ILoggerPlugin*>(Core::Plugins::instance().plugins()["logger"]);
    if (loggerPtr != NULL) {
        loggerPtr->log(ptr, datetime, txt, MESSAGE_ERROR);
    }
}
