#include "glossaryelement.h"


QString GlossaryElement::name() const
{
    return m_name;
}

void GlossaryElement::setName(const QString &name)
{
    m_name = name;
}

QString GlossaryElement::description() const
{
    return m_description;
}

void GlossaryElement::setDescription(const QString &description)
{
    m_description = description;
}
