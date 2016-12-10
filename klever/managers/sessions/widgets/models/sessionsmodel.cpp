#include "sessionsmodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include "sessionsqdjangomodel.h"

#include <QMessageBox>

SessionsModel::SessionsModel()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("sessions");
    m_db.open();

    QDjango::setDatabase(m_db);
    QDjango::registerModel<Sessions>();

    QDjango::createTables();

    updateModel();
}

SessionsModel::~SessionsModel()
{
    m_db.close();
}

QStringList SessionsModel::selectAllSessions()
{
    QDjangoQuerySet<Sessions> proms;
    QStringList tmp;

    tmp.clear();

    QList<QVariantMap> propertyMaps = proms.values(QStringList() <<  "name" << "parameters");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["name"].toString());
    }

    return tmp;
}

void SessionsModel::addSession(QString name, QString parameters) {

    QDjangoQuerySet<Sessions> sessions;

    bool isFind = false;

    QList<QVariantMap> propertyMaps = sessions.values(QStringList() << "name" << "parameters");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["name"].toString() == name) {
            isFind = true;
        }
    }

    if (!isFind) {
        Sessions *session = new Sessions;
        session->setName(name);
        session->setParameters(parameters);
        session->save();
    }
}

void SessionsModel::updateModel()
{
    setStringList(selectAllSessions());
}

void SessionsModel::deleteSession(const QModelIndex &index)
{
    QString name = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

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

void SessionsModel::renameSession(const QModelIndex &index, const QString &new_name)
{
    QString name = data(index, Qt::DisplayRole).toString();

    QDjangoQuerySet<Sessions> sessions;
    QDjangoQuerySet<Sessions> someSession;
    someSession = sessions.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));

    QList<QVariantMap> propertyMaps = someSession.values(QStringList() << "name" << "parameters");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["name"].toString() == name) {
            // Имена будут уникальные у сессий, поэтому тут всего 1 итарация будет
            someSession.at(0)->setName(new_name);
            someSession.at(0)->save();
            break;
        }
    }

    updateModel();
}

void SessionsModel::dublicateSession(const QModelIndex &index)
{
    QString name = data(index, Qt::DisplayRole).toString();

    QDjangoQuerySet<Sessions> sessions;
    QDjangoQuerySet<Sessions> someSession;
    someSession = sessions.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));

    QList<QVariantMap> propertyMaps = someSession.values(QStringList() << "name" << "parameters");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["name"].toString() == name) {
            // Имена будут уникальные у сессий, поэтому тут всего 1 итарация будет
            Sessions *session = new Sessions;
            session->setName(someSession.at(0)->name()+"_copy");
            session->setParameters(someSession.at(0)->parameters());
            session->save();
            break;
        }
    }

    updateModel();
}
