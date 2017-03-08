#include "sessionsmodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <library/message/messagelibrary.h>
#include "sessionsqdjangomodel.h"

#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>

SessionsModel::SessionsModel()
{
    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();
    }

    m_db.close();

}

SessionsModel::~SessionsModel(){}

QStringList SessionsModel::selectAllSessions()
{
    QStringList tmp;

    tmp.clear();

    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();
        QDjangoQuerySet<Sessions> proms;


        QList<QVariantMap> propertyMaps = proms.values(QStringList() <<  "name");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            tmp.append(propertyMap["name"].toString());
        }
    }

    m_db.close();

    return tmp;
}

/*
 * Получить информацию сессии
 */
QString SessionsModel::getSessionInformation(const QString &name)
{

    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();

        QDjangoQuerySet<Sessions> sessions;

        QList<QVariantMap> propertyMaps = sessions.values(QStringList() <<  "name" << "information");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == name) {
                return propertyMap["information"].toString();
            }
        }
    }

    m_db.close();

    return QString("");
}

/*
 * Установить информацию по сессии
 */
void SessionsModel::setSessionInformation(const QString &name, const QString &information)
{

    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();
        QDjangoQuerySet<Sessions> sessions;

        Sessions session;
        for (int i = 0; i < sessions.size(); ++i) {
            if (sessions.at(i, &session)) {
                if (session.name() == name) {
                    session.setInformation(information);
                    session.save();
                    break;
                }
            }
        }
    }

    m_db.close();
}

void SessionsModel::addSession(QString name, QString parameters) {


    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();

        QDjangoQuerySet<Sessions> sessions;

        bool isFind = false;

        QList<QVariantMap> propertyMaps = sessions.values(QStringList() << "name");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == name) {
                isFind = true;
            }
        }

        if (!isFind) {
            Sessions *session = new Sessions;
            session->setName(name);
            session->setParameters(parameters);
            session->setInformation("");
            session->save();
        }
    }
    m_db.close();
}

void SessionsModel::updateModel()
{
    setStringList(selectAllSessions());
}

void SessionsModel::deleteSession(const QModelIndex &index)
{
    QString name = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();

        QDjangoQuerySet<Sessions> sessions;
        QDjangoQuerySet<Sessions> someSession;
        someSession = sessions.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));

        QList<QVariantMap> propertyMaps = someSession.values(QStringList() << "name" << "parameters");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["name"].toString() == name) {
                someSession.remove();
            }
        }
    }

    m_db.close();

}

void SessionsModel::dublicateSession(const QModelIndex &index, const QString &cloneName)
{
    QString name = data(index, Qt::DisplayRole).toString();


    QSqlDatabase m_db = QSqlDatabase::database("sessions");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "sessions");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__sessions");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {

        QDjango::setDatabase(m_db);
        QDjango::registerModel<Sessions>();
        QDjango::createTables();

        QDjangoQuerySet<Sessions> sessions;

        Sessions session;

        for (int i = 0; i < sessions.size(); ++i) {
            if (sessions.at(i, &session)) {
                if (session.name() == cloneName) {
                    messageLibrary msg;
                    msg.createErrorMessage("Ошибка", "Имя копии уже существует, выберите другое имя!");
                    return;
                }
            }
        }

        for (int i = 0; i < sessions.size(); ++i) {
            if (sessions.at(i, &session)) {
                if (session.name() == name) {
                    Sessions clone;
                    clone.setName(cloneName);
                    clone.setParameters(session.parameters());
                    clone.setInformation(session.information());
                    clone.save();
                    break;
                }
            }
        }

        updateModel();

    }

    m_db.close();
}
