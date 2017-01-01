#include "usermodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <QDebug>
#include "userqdjangomodel.h"
#include <QCoreApplication>

#include <library/message/messagelibrary.h>

UserModel::UserModel()
{

    m_db = QSqlDatabase::database("autorization");
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
        QDjango::registerModel<User>();

        QDjango::createTables();
    }

}

UserModel::~UserModel()
{
    m_db.close();
}

QStringList UserModel::selectAllUsers()
{
    QDjangoQuerySet<User> users;
    QStringList tmp;

    tmp.clear();

    QList<QVariantMap> propertyMaps = users.values(QStringList() << "username" << "password" << "group");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["username"].toString());
    }

    return tmp;
}

void UserModel::addUser(QString username, QString password, QString group) {
    User *user = new User;
    user->setUsername(username);
    user->setPassword(password);
    user->setGroup(group);
    user->save();
}

QString UserModel::getUserPasswordByName(QString username) {
    QDjangoQuerySet<User> users;
    QStringList tmp;

    tmp.clear();

    QList<QVariantMap> propertyMaps = users.values(QStringList() << "username" << "password" << "group");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        if (propertyMap["username"].toString() == username) {
            return propertyMap["password"].toString();
        }
    }

    return QString("");
}

void UserModel::updateModel()
{
    setStringList(selectAllUsers());
}

void UserModel::deleteUser(const QModelIndex &index)
{
    QStringList usersList;
    usersList.clear();

    QString username = data(index, Qt::DisplayRole).toString();
    removeRows(0, 1, index);

    QDjangoQuerySet<User> users;
    QDjangoQuerySet<User> someUsers;
    someUsers = users.filter(QDjangoWhere("username", QDjangoWhere::Equals, username));
    someUsers.remove();
}
