#include "architectlinks.h"

QString ArchitectLinks::name() const
{
    return m_name;
}

void ArchitectLinks::setName(const QString &name)
{
    m_name = name;
}

QString ArchitectLinks::linkA() const
{
    return m_linkA;
}

void ArchitectLinks::setLinkA(const QString &linkA)
{
    m_linkA = linkA;
}

QString ArchitectLinks::linkB() const
{
    return m_linkB;
}

void ArchitectLinks::setLinkB(const QString &linkB)
{
    m_linkB = linkB;
}

QString ArchitectLinks::linkACount() const
{
    return m_linkACount;
}

void ArchitectLinks::setLinkACount(const QString &linkACount)
{
    m_linkACount = linkACount;
}

QString ArchitectLinks::linkBCount() const
{
    return m_linkBCount;
}

void ArchitectLinks::setLinkBCount(const QString &linkBCount)
{
    m_linkBCount = linkBCount;
}

QString ArchitectLinks::type() const
{
    return m_type;
}

void ArchitectLinks::setType(const QString &type)
{
    m_type = type;
}

QString ArchitectLinks::description() const
{
    return m_description;
}

void ArchitectLinks::setDescription(const QString &description)
{
    m_description = description;
}
