#include "pluginslistqdjangomodel.h"

QString PluginsQDjangoModel::name() const
{
  return m_name;
}

void PluginsQDjangoModel::setName(const QString &name)
{
  m_name = name;
}

