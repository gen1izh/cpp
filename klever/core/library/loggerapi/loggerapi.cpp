#include "loggerapi.h"
#include "../glabals.h"

// Журналирование информационного сообщения
void Library::Logger::logInfo(QObject *ptr, QString txt)
{
    if (loggerPtr != NULL) {
        loggerPtr->log(ptr, txt, MESSAGE_INFO);
    }
}

// Журналирование сообщения предупреждения
void Library::Logger::logWarning(QObject *ptr, QString txt) {
    if (loggerPtr != NULL) {
        loggerPtr->log(ptr, txt, MESSAGE_WARNING);
    }
}

// Журналирование сообщения с ошибкой
void Library::Logger::logError(QObject *ptr, QString txt) {
    if (loggerPtr != NULL) {
        loggerPtr->log(ptr, txt, MESSAGE_ERROR);
    }
}
