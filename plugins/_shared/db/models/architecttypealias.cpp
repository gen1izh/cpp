#include "architecttypealias.h"



QString ArchitectTypeAlias::type() const
{
    return m_type;
}

void ArchitectTypeAlias::setType(const QString &type)
{
    m_type = type;
}

QString ArchitectTypeAlias::alias() const
{
    return m_alias;
}

void ArchitectTypeAlias::setAlias(const QString &alias)
{
    m_alias = alias;
}
