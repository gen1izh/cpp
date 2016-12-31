#include "userqdjangomodel.h"

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
QString User::group() const
{
  return m_group;
}

void User::setGroup(const QString &group)
{
  m_group = group;
}


