#include "userqdjangomodel.h"


User::User(QObject *parent)
    : QDjangoModel(parent)
{
    setForeignKey("group", new Group(this));
}

Group *User::group() const
{
    return qobject_cast<Group *>(foreignKey("group"));
}

void User::setGroup(Group *group)
{
     setForeignKey("group", group);
}

QString User::username() const
{
    return m_username;
}

void User::setUsername(const QString &username)
{
    m_username = username;
}

QString User::password() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}


