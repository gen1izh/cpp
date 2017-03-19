#include "groupqdjangomodel.h"

Group::Group(QObject *parent)
    : QDjangoModel(parent) {

}

QString Group::name() const
{
    return m_name;
}

void Group::setName(const QString &name)
{
    m_name = name;
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
