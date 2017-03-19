#include "roleqdjangomodel.h"

Role::Role(QObject *parent)
    : QDjangoModel(parent)
{
    setForeignKey("group", new Group(this));
}

QString Role::name() const
{
    return m_name;
}

void Role::setName(const QString &name)
{
    m_name = name;
}

Group *Role::group() const
{
    return qobject_cast<Group *>(foreignKey("group"));
}

void Role::setGroup(Group *group)
{
     setForeignKey("group", group);
}




