#include "pluginslistqdjangomodel.h"



QString PluginsQDjangoModel::name() const
{
  return m_name;
}

void PluginsQDjangoModel::setName(const QString &name)
{
  m_name = name;
}

bool PluginsQDjangoModel::state() const
{
  return m_state;
}

void PluginsQDjangoModel::setState(bool state)
{
  m_state = state;
}

int PluginsQDjangoModel::objectsCount() const
{
  return m_objectsCount;
}

void PluginsQDjangoModel::setObjectsCount(int objectsCount)
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
