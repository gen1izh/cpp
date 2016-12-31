#ifndef USERQDJANGOMODEL_H
#define USERQDJANGOMODEL_H

#include <library/orm/db/QDjangoModel.h>

class User : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(QString group READ group WRITE setGroup)

    Q_CLASSINFO("username", "max_length=255")
    Q_CLASSINFO("password", "max_length=128")
    Q_CLASSINFO("group", "max_length=128")

public:
    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    QString group() const;
    void setGroup(const QString &group);

private:
    QString m_username;
    QString m_password;
    QString m_group;
};

#endif // USERQDJANGOMODEL_H
