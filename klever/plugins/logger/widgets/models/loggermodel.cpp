#include "loggermodel.h"

#include <library/message/messagelibrary.h>

#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

#include <frameWork/base.h>

LoggerModel::LoggerModel()
{
    QString path = Core::Base::instance().getParameterValue(QString("[Session]Folder"), QString(""));
    path += "/logs";

    QDir dir(path);
    if (!dir.exists()) {
        if (!dir.mkpath(path)) {
            Library::LoggerApi::logError(this, "Каталог журналов не создан!");
        }
    }

    path = QString("%1/%2").arg(path).arg("__logger");

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<LoggerQDjangoModel>();

    QDjango::createTables();
}

LoggerModel::~LoggerModel()
{

}


QStringList LoggerModel::filtredSources(QDjangoQuerySet<LoggerQDjangoModel> someMessages,
                                        const QStringList &sources) {

    QString type;
    QStringList tmp;

    QList<QVariantMap> propertyMaps = someMessages.values(QStringList() << "source"
                                                                        << "datetime" << "txt" << "type");
    foreach (const QVariantMap &propertyMap, propertyMaps) {

        if (sources.contains(propertyMap["source"].toString())) {

            if (propertyMap["type"].toString() == "error") {
                type = "<font color='red'><b>[Ошибка]</b></font>";
            }
            if (propertyMap["type"].toString() == "warning"){
                type = "<font color='orange'><b>[Предупреждение]</b></font>";
            }
            if (propertyMap["type"].toString() == "information") {
                type = "<font color='blue'><b>[Информация]</b></font>";
            }

            QString msg = QString("%1 <b>%2</b> <i>%3</i>  --> %4")
                                    .arg(type)
                                    .arg(propertyMap["source"].toString())
                                    .arg(propertyMap["datetime"].toString())
                                    .arg(propertyMap["txt"].toString());
            tmp.append(msg);
        }
    }
    return tmp;
}

QStringList LoggerModel::filtredMessages(const QString &startDateTime, const QString &endDateTime,
                                         bool isError, bool isWarning, bool isInformation,
                                         const QStringList &sources)
{
    QDjangoQuerySet<LoggerQDjangoModel> messages;
    QStringList tmp;

    tmp.clear();

    QDjangoQuerySet<LoggerQDjangoModel> someErrorMessages;
    QDjangoQuerySet<LoggerQDjangoModel> someWarningMessages;
    QDjangoQuerySet<LoggerQDjangoModel> someInformationMessages;

    if (isError) {
        someErrorMessages = messages.filter(QDjangoWhere("type", QDjangoWhere::Equals, "error"));
        tmp += filtredSources(someErrorMessages, sources);
    }
    if (isWarning) {
        someWarningMessages = messages.filter(QDjangoWhere("type", QDjangoWhere::Equals, "warning"));
        tmp += filtredSources(someWarningMessages, sources);
    }
    if (isInformation) {
        someInformationMessages = messages.filter(QDjangoWhere("type", QDjangoWhere::Equals, "information"));
        tmp += filtredSources(someInformationMessages, sources);
    }

    return tmp;
}

QStringList LoggerModel::getSources()
{
    QDjangoQuerySet<LoggerQDjangoModel> messages;
    QStringList tmp;

    tmp.clear();

    QList<QVariantMap> propertyMaps = messages.values(QStringList() << "source");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["source"].toString());
    }

    tmp.removeDuplicates();

    return tmp;
}

/*
 * Добавить запись в журнал
 */
void LoggerModel::addMessage(const QString &source, const QString &datetime, const QString &txt, const QString &type)
{ 
    QSqlDatabase m_db = QSqlDatabase::database("logger");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "logger");
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
        QDjango::registerModel<LoggerQDjangoModel>();

        QDjango::createTables();

        LoggerQDjangoModel *log = new LoggerQDjangoModel;
        log->setSource(source);
        log->setDatetime(datetime);
        log->setTxt(txt);
        log->setType(type);
        log->save();

    }

    m_db.close();
}





