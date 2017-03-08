#include "termselement.h"



QString TermsElement::name() const
{
    return m_name;
}

void TermsElement::setName(const QString &name)
{
    m_name = name;
}

QString TermsElement::description() const
{
    return m_description;
}

void TermsElement::setDescription(const QString &description)
{
    m_description = description;
}
