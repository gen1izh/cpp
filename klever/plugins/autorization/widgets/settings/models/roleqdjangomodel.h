#ifndef ROLE_QDJANGO_MODEL_H
#define ROLE_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>
#include "groupqdjangomodel.h"

class Role : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(Group *group READ group WRITE setGroup)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("group", "on_delete=cascade")

public:
    Role(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    Group *group() const;
    void setGroup(Group *group);


private:
    QString m_name;
};

#endif // ROLE_QDJANGO_MODEL_H
