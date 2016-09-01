#include "usermodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include "userqdjangomodel.h"

UserModel::UserModel()
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("autoriz");
    m_db.open();

    QDjango::setDatabase(m_db);
    QDjango::registerModel<User>();

    QDjango::createTables();

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
