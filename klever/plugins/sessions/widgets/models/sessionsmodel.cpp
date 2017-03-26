#include "sessionsmodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <library/message/messagelibrary.h>
#include "sessionsqdjangomodel.h"

#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <frameWork/base.h>

SessionsModel::SessionsModel()
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Sessions>();
    QDjango::createTables();
}

SessionsModel::~SessionsModel(){}

QStringList SessionsModel::selectAllSessions()
{
    QStringList tmp;

    tmp.clear();

    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Sessions>();
    QDjango::createTables();
    QDjangoQuerySet<Sessions> proms;


    QList<QVariantMap> propertyMaps = proms.values(QStringList() <<  "name");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["name"].toString());
    }

    return tmp;
}

/*
 * Получить информацию сессии
 */
QString SessionsModel::getSessionInformation(const QString &name)
{
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<Sessions>();
    QDjango::createTables();

    QDjangoQuerySet<Sessions> sessions;

    QList<QVariantMap> propertyMaps = sessions.values(QStringList() <<  "name" << "information");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["name"].toString() == name) {
            return propertyMap["information"].toString();
        }
    }

    return QString("");
}

/*
 * Установить информацию по сессии
 */
void SessionsModel::setSessionInformation(const QString &name, const QString &information)
{
    QDjango::setDatabase(*Core::Base::instance().database());
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

void SessionsModel::addSession(QString name, QString parameters) {

    QDjango::setDatabase(*Core::Base::instance().database());
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

    // Создаем специальную БД сессии
    QSqlQuery query(QString("CREATE DATABASE %1").arg(name), *Core::Base::instance().database());

//    if (!query.isValid()) {
//        messageLibrary msg;
//        msg.createErrorMessage("Ошибка", "Не удаллось создать БД");
//    }

}

void SessionsModel::updateModel()
{
    setStringList(selectAllSessions());
}

void SessionsModel::deleteSession(const QModelIndex &index)
{
    QString name = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

    QDjango::setDatabase(*Core::Base::instance().database());
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

void SessionsModel::dublicateSession(const QModelIndex &index, const QString &cloneName)
{
    QString name = data(index, Qt::DisplayRole).toString();

    QDjango::setDatabase(*Core::Base::instance().database());
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
