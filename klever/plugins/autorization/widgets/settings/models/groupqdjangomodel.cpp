#include "groupqdjangomodel.h"


//Group::Group(QObject *parent)
//{
//    setForeignKey("role", new Role());
//}

//Role *Group::role() const
//{
//    return qobject_cast<Role *>(foreignKey("role"));
//}

//void Group::setRole(Role *role)
//{
//     setForeignKey("role", role);
//}

QString Group::name() const
{
    return m_name;
}

void Group::setName(const QString &name)
{
    m_name = name;
}

QString Group::role() const
{
    return m_role;
}

void Group::setRole(const QString &role)
{
    m_role = role;
}

void Group::setDescription(const QString &description)
{
    m_description = description;
}

QString Group::description() const
{
    return m_description;
}

QString Group::parent() const
{
    return m_parent;
}

void Group::setParent(const QString &parent)
{
    m_parent = parent;
}
