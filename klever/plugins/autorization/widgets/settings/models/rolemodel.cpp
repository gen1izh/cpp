#include "rolemodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <QDebug>
#include <QCoreApplication>
#include <library/message/messagelibrary.h>

RoleModel::RoleModel()
{

    QSqlDatabase m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {
        QDjango::setDatabase(m_db);
        QDjango::registerModel<Role>();
        QDjango::createTables();
    }

    m_db.close();

}

RoleModel::~RoleModel(){}

QStringList RoleModel::selectAllRoles()
{
    QStringList tmp;
    tmp.clear();

    QSqlDatabase m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {
        QDjango::setDatabase(m_db);
        QDjango::registerModel<Role>();
        QDjango::createTables();
        QDjangoQuerySet<Role> roles;


        QList<QVariantMap> propertyMaps = roles.values(QStringList() << "name" << "promission");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            tmp.append(propertyMap["name"].toString());
        }
    }

    m_db.close();

    return tmp;
}

void RoleModel::addRole(QString name, QString promission) {
    QSqlDatabase m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {
        QDjango::setDatabase(m_db);
        QDjango::registerModel<Role>();
        QDjango::createTables();
        Role *role = new Role;
        role->setName(name);
        role->setPromission(promission);
        role->save();
    }
    m_db.close();
}

void RoleModel::updateModel()
{
    setStringList(selectAllRoles());
}

void RoleModel::deleteRole(const QModelIndex &index)
{
    QStringList rolesList;
    rolesList.clear();

    QString name = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

    QSqlDatabase m_db = QSqlDatabase::database("autorization");
    if (m_db.driverName()!="QSQLITE") {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "autorization");
    }

    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__autorization");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

        msg.createErrorMessage("Ошибка", text);

    }
    else {
        QDjango::setDatabase(m_db);
        QDjango::registerModel<Role>();
        QDjango::createTables();

        QDjangoQuerySet<Role> roles;
        roles = roles.filter(QDjangoWhere("name", QDjangoWhere::Equals, name));
        roles.remove();


        QDjangoQuerySet<Group> groups;
        groups = groups.filter(QDjangoWhere("role", QDjangoWhere::Equals, name));

        Group group;
        for (int i = 0; i < groups.size(); ++i) {
            if (groups.at(i, &group)) {
                group.setRole(QString(""));
                group.save();
            }
        }
    }

    m_db.close();

}
