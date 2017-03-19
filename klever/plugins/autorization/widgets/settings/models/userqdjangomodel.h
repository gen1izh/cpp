#ifndef USERQDJANGOMODEL_H
#define USERQDJANGOMODEL_H

#include <library/orm/db/QDjangoModel.h>

#include "groupqdjangomodel.h"

class User : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername)
    Q_PROPERTY(QString password READ password WRITE setPassword)
    Q_PROPERTY(Group *group READ group WRITE setGroup)

    Q_CLASSINFO("username", "max_length=255")
    Q_CLASSINFO("password", "max_length=128") 
    Q_CLASSINFO("group", "on_delete=cascade")

public:

    User(QObject *parent = 0);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    Group *group() const;
    void setGroup(Group *group);

private:
    QString m_username;
    QString m_password;
};

#endif // USERQDJANGOMODEL_H
