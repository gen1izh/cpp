
#include "logger.h"
#include <QMainWindow>
#include <library/utilsLibrary/utilslibrary.h>
#include <frameWork/base.h>
#include <interfaces/ilogger.h>


Logger::Logger()
{
    setName(QString("logger"));
    setTextName(tr("Журнал"));
    m_settings = NULL;

    m_watcherAction = new QAction(QIcon(":/images/base/watcher.png"),
                                  tr("&Просмотр журналов"));
    m_watcherAction->setStatusTip(tr("Просмотр журналов"));

    m_scripts = new LogerScriptApi();

    // Регистрация этого объекта в движке исполнения
    QScriptValue value = Core::Base::instance().scriptEngine()->newQObject(m_scripts);
    Core::Base::instance().addToGlobalValueList(value);
    Core::Base::instance().scriptEngine()->globalObject().setProperty(QString("log"), value);

    m_thread = new LThread();
    m_thread->start();
}

Logger::~Logger()
{

}

QWidget *Logger::settingPage()
{
    if (m_settings == NULL) {
      m_settings = new SettingsForm();
    }
    return m_settings;
}

/*
 * Создание виджетов
 */
void Logger::createWidgets()
{
    _widgetActionList[tr("(Logger)SettingsForm")].first  = new SettingsForm();
    _widgetActionList[tr("(Logger)SettingsForm")].second = NULL;

    _widgetActionList[tr("(Logger)LoggerForm")].first  = new LoggerForm();
    _widgetActionList[tr("(Logger)LoggerForm")].second = NULL;

    // Добавляем просмотрщик журналов
    _widgetActionList[tr("(Logger)Watcher")].first  = new WatcherForm();
    _widgetActionList[tr("(Logger)Watcher")].second = m_watcherAction;
}

void Logger::createActions()
{

}

void Logger::createConnectors()
{
    QObject::connect(m_thread, SIGNAL(sendMessage(const QString&)),
                     this, SLOT(drawMessage(const QString&)));
}

QString Logger::information()
{
    QString msg = "logger";

    return msg;
}

QIcon Logger::settingIcon()
{
    return QIcon(":/settings/img/log.png");
}

/*
 *
 */
void Logger::drawMessage(const QString& msg) {
    static_cast<LoggerForm*>(_widgetActionList[tr("(Logger)LoggerForm")].first)->appendText(msg);
}

/*
 * Основная функция для протоколирования.
 */
void Logger::log(QObject *ptr,
                 const QString &datetime,
                 const QString &txt,
                 MessagesTypes type) {


    WatcherForm *t = static_cast<WatcherForm*>(_widgetActionList[tr("(Logger)Watcher")].first);

    QString stringType;

    if (type==MESSAGE_ERROR) stringType = "error";
    if (type==MESSAGE_WARNING) stringType = "warning";
    if (type==MESSAGE_INFO)  stringType = "information";

    t->loggerModel()->addMessage(ptr->objectName(), datetime, txt, stringType);

    logPacket pkt;

    pkt.ptr = ptr;
    pkt.datetime = datetime;
    pkt.txt = txt;
    pkt.type = type;

    m_thread->appendItemToLogList(pkt);


}

