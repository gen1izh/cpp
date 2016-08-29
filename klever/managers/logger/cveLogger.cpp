
#include "cveLogger.h"
#include <QMainWindow>
#include <library/utilsLibrary/utilslibrary.h>
#include <managers/logger/logger/logger.h>
#include <frameWork/cve.h>
#include <interfaces/ilogger.h>

#include "widgets/loggerstabswidgets.h"
#include "widgets/loggerswatcherwidget.h"

/*
 * Функция журналирования сообщения
 */
CveLogger::CveLogger()
{
  setName(QString("/logger"));
  setTextName(tr("Журналы"));
  _settings = NULL;

  _loggersWatcherAct = new QAction(
        QIcon(":/logger/img/logwatcher.png"),
        tr("&Просмотр журналов"), this);
  _loggersWatcherAct->setStatusTip(
        tr("Просмотр журналов"));

  _scripts = new LogerScriptApi();

  // Регистрация этого объекта в движке исполнения
  QScriptValue value = Cve::instance().scriptEngine()->newQObject(_scripts);
  Cve::instance().addToGlobalValueList(value);
  Cve::instance().scriptEngine()->globalObject().setProperty(QString("log"), value);


}

/*
 * Создание виджетов
 */
void CveLogger::createWidgets()
{
  // Добавляем  табы с журналами
  widgetActionList[tr("(LoggerManager)loggersTabsWidgets")].first  = new LoggersTabsWidgets();
  widgetActionList[tr("(LoggerManager)loggersTabsWidgets")].second = NULL;

  // Добавляем просмотрщик журналов
  widgetActionList[tr("(LoggerManager)loggersWatcherWidget")].first  =
      new LoggersWatcherWidget(NULL,
                               (LoggersTabsWidgets *)
                               widgetActionList[tr("(LoggerManager)loggersTabsWidgets")].first);

  widgetActionList[tr("(LoggerManager)loggersWatcherWidget")].second = _loggersWatcherAct;

}

/*
 * Основная функция для протоколирования.
 * При разработке менеджера журналирования ее необходимо переопределить.
 */
void CveLogger::log(QObject       *ptr,
                    QString        txt,
                    MessagesTypes  type,
                    LoggersTypes   loggertype) {

  // TODO хак
  LoggersTabsWidgets *lo =
      (LoggersTabsWidgets *)
      widgetActionList[tr("(LoggerManager)loggersTabsWidgets")].first;

  if (lo->loggers()->value(loggertype) != NULL) {
    if ( type == MESSAGE_ERROR ) {
      lo->loggers()->value(loggertype)->errorMessage(ptr, txt);
    }
    else if ( type == MESSAGE_WARNING ) {
      lo->loggers()->value(loggertype)->warnMessage(ptr, txt);
    }
    else if ( type == MESSAGE_INFO ) {
      lo->loggers()->value(loggertype)->infoMessage(ptr, txt);
    }
    else {
      qDebug().noquote() << QString("Неправильно задан тип сообщения!");
    }
  }
  else {
    qDebug().noquote()  << QString("Журнала не существует! Msg = %2 ").arg(txt);
  }
}

