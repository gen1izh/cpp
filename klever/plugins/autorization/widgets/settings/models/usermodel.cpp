#include "usermodel.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <QDebug>
#include "userqdjangomodel.h"
#include <QCoreApplication>

#include <library/message/messagelibrary.h>

UserModel::UserModel()
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
        QDjango::registerModel<User>();

        QDjango::createTables();
    }

    m_db.close();

}

UserModel::~UserModel()
{
}

QStringList UserModel::selectAllUsers()
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
        QDjango::registerModel<User>();

        QDjango::createTables();
        QDjangoQuerySet<User> users;


        QList<QVariantMap> propertyMaps = users.values(QStringList() << "username" << "password" << "group");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            tmp.append(propertyMap["username"].toString());
        }

    }

    m_db.close();

    return tmp;
}

void UserModel::addUser(QString username, QString password, QString group) {

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
        QDjango::registerModel<User>();

        QDjango::createTables();
        User *user = new User;
        user->setUsername(username);
        user->setPassword(password);
        user->setGroup(group);
        user->save();
    }

    m_db.close();
}

QString UserModel::getUserPasswordByName(QString username) {
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
        QDjango::registerModel<User>();

        QDjango::createTables();
        QDjangoQuerySet<User> users;

        QList<QVariantMap> propertyMaps = users.values(QStringList() << "username" << "password" << "group");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            if (propertyMap["username"].toString() == username) {
                return propertyMap["password"].toString();
            }
        }
    }

    m_db.close();

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
        QDjango::registerModel<User>();
        QDjango::createTables();

        QDjangoQuerySet<User> users;
        QDjangoQuerySet<User> someUsers;
        someUsers = users.filter(QDjangoWhere("username", QDjangoWhere::Equals, username));
        someUsers.remove();
    }

    m_db.close();
}
