#ifndef ROLE_QDJANGO_MODEL_H
#define ROLE_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class Role : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString promission READ promission WRITE setPromission)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("promission", "max_length=128")

public:
    QString name() const;
    void setName(const QString &name);

    QString promission() const;
    void setPromission(const QString &promission);

private:
    QString m_name;
    QString m_promission;
};

#endif // ROLE_QDJANGO_MODEL_H
