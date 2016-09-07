#include "loggerapi.h"

// Журналирование информационного сообщения
void Library::LoggerApi::logInfo(QObject *ptr, QString txt)
{
    if (Utilities::loggerPtr() != NULL) {
        Utilities::loggerPtr()->log(ptr, txt, MESSAGE_INFO);
    }
}

// Журналирование сообщения предупреждения
void Library::LoggerApi::logWarning(QObject *ptr, QString txt) {
    if (Utilities::loggerPtr() != NULL) {
        Utilities::loggerPtr()->log(ptr, txt, MESSAGE_WARNING);
    }
}

// Журналирование сообщения с ошибкой
void Library::LoggerApi::logError(QObject *ptr, QString txt) {
    if (Utilities::loggerPtr() != NULL) {
        Utilities::loggerPtr()->log(ptr, txt, MESSAGE_ERROR);
    }
}



ILogger *Library::LoggerApi::Utilities::loggerPtr()
{
    return m_loggerPtr;
}

void Library::LoggerApi::Utilities::setLoggerPtr(ILogger *loggerPtr)
{
    m_loggerPtr = loggerPtr;
}
