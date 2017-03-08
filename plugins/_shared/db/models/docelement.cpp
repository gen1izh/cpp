#include "docelement.h"


QString DocElement::name() const
{
    return m_name;
}

void DocElement::setName(const QString &name)
{
    m_name = name;
}

QString DocElement::description() const
{
    return m_description;
}

void DocElement::setDescription(const QString &description)
{
    m_description = description;
}

QString DocElement::type() const
{
    return m_type;
}

void DocElement::setType(const QString &type)
{
    m_type = type;
}
