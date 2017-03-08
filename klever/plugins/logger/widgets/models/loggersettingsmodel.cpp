#include "loggersettingsmodel.h"

#include <library/message/messagelibrary.h>

#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

#include <frameWork/base.h>

LoggerSettingsModel::LoggerSettingsModel()
{
    m_db = QSqlDatabase::database("loggerSettings");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "loggerSettings");
    }

    QString path = Core::Base::instance().getParameterValue(QString("[Session]Folder"), QString(""));
    path += "/logs";

    QDir dir(path);
    if (!dir.exists()) {
        if (!dir.mkpath(path)) {
            Library::LoggerApi::logError(this, "Каталог журналов не создан!");
        }
    }

    path = QString("%1/%2").arg(path).arg("__logger");

    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {
        QDjango::setDatabase(m_db);
        QDjango::registerModel<LoggerSettingsQDjangoModel>();
        QDjango::createTables();
    }
}

LoggerSettingsModel::~LoggerSettingsModel()
{
    m_db.close();
}

/*
 *
 */
void LoggerSettingsModel::setCurrentName(const QString &currentName)
{
    QDjangoQuerySet<LoggerSettingsQDjangoModel> settings;

    for (int i = 0; i < settings.size(); ++i) {
        LoggerSettingsQDjangoModel setting;
        if (settings.at(i, &setting)) {
            setting.setCurrentLoggerName(currentName);
            setting.save();
            return;
        }
    }
    LoggerSettingsQDjangoModel *setting = new LoggerSettingsQDjangoModel;
    setting->setCurrentLoggerName(currentName);
    setting->save();
}


/*
 *
 */
QString LoggerSettingsModel::getCurrentName()
{
    QDjangoQuerySet<LoggerSettingsQDjangoModel> settings;

    LoggerSettingsQDjangoModel setting;
    for (int i = 0; i < settings.size(); ++i) {
        if (settings.at(i, &setting)) {
            return setting.currentLoggerName();
        }
    }
    return QString("");
}
