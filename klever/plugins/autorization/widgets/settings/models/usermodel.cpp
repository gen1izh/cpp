#include "usermodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <QDebug>
#include "userqdjangomodel.h"
#include <QCoreApplication>
#include <frameWork/base.h>
#include <library/message/messagelibrary.h>

UserModel::UserModel()
{
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjango::registerModel<User>();
    QDjango::createTables();

    QDjangoQuerySet<Group> groups;
    groups = groups.filter(QDjangoWhere("name", QDjangoWhere::Equals, "Administrators"));

    if (groups.count()==0) {
        messageLibrary msg;
        msg.createInfoMessage("Информация", "Группы администраторов нет, пользователя создать не могу!");
    }
    else {
        // Создаем пользователя по-умолчанию
        QDjangoQuerySet<User> users;
        users = users.filter(QDjangoWhere("username", QDjangoWhere::Equals, "Administrator"));

        qDebug() << users.count();

        if (users.count()==0) {
            User _user;
            _user.setUsername("Administrator");
            _user.setPassword("admin");
            _user.setGroup(groups.at(0));
            _user.save();
        }
    }
}

UserModel::~UserModel()
{
}

QStringList UserModel::selectAllUsers()
{
    QStringList tmp;
    tmp.clear();

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjango::registerModel<User>();
    QDjango::createTables();

    QDjangoQuerySet<User> users;

    QList<QVariantMap> propertyMaps = users.values(QStringList() << "username" << "password");
    foreach (const QVariantMap &propertyMap, propertyMaps) {
        tmp.append(propertyMap["username"].toString());
    }

    return tmp;
}

void UserModel::addUser(QString username, QString password, Group *group) {

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjango::registerModel<User>();
    QDjango::createTables();
    User *user = new User;
    user->setUsername(username);
    user->setPassword(password);
    user->setGroup(group);
    user->save();
}

QString UserModel::getUserPasswordByName(QString username) {
    QStringList tmp;
    tmp.clear();

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjango::registerModel<User>();
    QDjango::createTables();
    QDjangoQuerySet<User> users;

    QList<QVariantMap> propertyMaps = users.values(QStringList() << "username" << "password" );
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

    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjango::registerModel<User>();
    QDjango::createTables();
    QDjangoQuerySet<User> users;
    users = users.filter(QDjangoWhere("username", QDjangoWhere::Equals, username));
    users.remove();
}
