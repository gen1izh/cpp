#include "pluginslistqdjangomodel.h"

QString PluginsQDjangoModel::name() const
{
  return m_name;
}

void PluginsQDjangoModel::setName(const QString &name)
{
  m_name = name;
}

QString PluginsQDjangoModel::state() const
{
    return m_state;
}

void PluginsQDjangoModel::setState(const QString &state)
{
    m_state = state;
}

QString PluginsQDjangoModel::objectsCount() const
{
    return m_objectsCount;
}

void PluginsQDjangoModel::setObjectsCount(const QString &objectsCount)
{
    m_objectsCount = objectsCount;
}

QString PluginsQDjangoModel::type() const
{
    return m_type;
}

void PluginsQDjangoModel::setType(const QString &type)
{
    m_type = type;
}
