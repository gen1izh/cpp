#include "loggerapi.h"
#include <frameWork/cve.h>
/*
 *  Журналирование информационного сообщения. Журнал системный (по-умолчанию)
 */
void Library::LoggerApi::logInfo(QObject *ptr, QString txt)
{
  if (Cve::instance().getParameterValue(QString("loggerReady"),false)) {
    CveManager::instance().logger()->log(ptr,txt,MESSAGE_INFO);
  }
}

/*
 * Журналирование сообщения предупреждения. Журнал системный (по-умолчанию)
 */
void Library::LoggerApi::logWarning(QObject *ptr, QString txt) {
  if (Cve::instance().getParameterValue(QString("loggerReady"),false)) {
    CveManager::instance().logger()->log(ptr,txt,MESSAGE_WARNING);
  }
}

/*
 * Журналирование сообщения с ошибкой. Журнал системный (по-умолчанию)
 */
void Library::LoggerApi::logError(QObject *ptr, QString txt) {
  if (Cve::instance().getParameterValue(QString("loggerReady"),false)) {
    CveManager::instance().logger()->log(ptr,txt,MESSAGE_ERROR);
  }
}

/*
 * Журналирование информационного сообщения. Журнал модулей
 */
void Library::LoggerApi::logInfo_ToModuleJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_INFO,MODULE_LOG);
}

/*
 * Журналирование сообщения предупреждения. Журнал модулей
 */
void Library::LoggerApi::logWarning_ToModuleJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_WARNING,MODULE_LOG);
}

/*
 * Журналирование сообщения об ошибке. Журнал модулей
 */
void Library::LoggerApi::logError_ToModuleJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_ERROR,MODULE_LOG);
}

/*
 * Журналирование информационного сообщения. Журнал пользователя
 */
void Library::LoggerApi::logInfo_ToUserJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_INFO,USER_LOG);
}

/*
 * Журналирование информационного сообщения. Журнал пользователя
 */
void Library::LoggerApi::logWarning_ToUserJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_WARNING,USER_LOG);
}

/*
 * Журналирование информационного сообщения. Журнал пользователя
 */
void Library::LoggerApi::logError_ToUserJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_ERROR,USER_LOG);
}

/*
 * Журналирование информационного сообщения. Журнал скриптов
 */
void Library::LoggerApi::logInfo_ToScriptJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_INFO,SCRIPT_LOG);
}

/*
 *  Журналирование информационного сообщения. Журнал скриптов
 */
void Library::LoggerApi::logWarning_ToScriptJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_WARNING,SCRIPT_LOG);
}

/*
 * Журналирование информационного сообщения. Журнал скриптов
 */
void Library::LoggerApi::logError_ToScriptJournal(QObject *ptr, QString txt) {
  CveManager::instance().logger()->log(ptr,txt,MESSAGE_ERROR,SCRIPT_LOG);
}
