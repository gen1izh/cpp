#include "logerscriptapi.h"
#include "frameWork/base.h"

using namespace Library::LoggerApi;

LogerScriptApi::LogerScriptApi(QObject *parent) : QObject(parent){}

/*
 * Журналирование ошибочного сообщения в журнал
 */
void LogerScriptApi::error(QString txt) {
  logError(Core::Base::instance().operations(), txt);
}

/*
 * Журналирование сообщения предупреждения в журнал
 */
void LogerScriptApi::warning(QString txt) {
  logWarning(Core::Base::instance().operations(), txt);
}

/*
 * Журналирование информационного сообщения в журнал
 */
void LogerScriptApi::information(QString txt) {
  logInfo(Core::Base::instance().operations(), txt);
}

