#include "logerscriptapi.h"
#include "frameWork/cve.h"

using namespace Library::LoggerApi;

LogerScriptApi::LogerScriptApi(QObject *parent) : QObject(parent){}

/*
 * Журналирование ошибочного сообщения в журнал
 */
void LogerScriptApi::error(QString txt) {
  logError_ToScriptJournal(Cve::instance().operations(), txt);
}

/*
 * Журналирование сообщения предупреждения в журнал
 */
void LogerScriptApi::warning(QString txt) {
  logWarning_ToScriptJournal(Cve::instance().operations(), txt);
}

/*
 * Журналирование информационного сообщения в журнал
 */
void LogerScriptApi::information(QString txt) {
  logInfo_ToScriptJournal(Cve::instance().operations(), txt);
}

