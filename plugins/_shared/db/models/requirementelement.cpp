#include "requirementelement.h"


QString RequirementElement::rtype() const
{
    return m_rtype;
}

void RequirementElement::setRType(const QString &rtype)
{
    m_rtype = rtype;
}

int RequirementElement::identificator() const
{
    return m_identificator;
}

void RequirementElement::setIdentificator(const int &identificator)
{
    m_identificator = identificator;
}

QString RequirementElement::name() const
{
    return m_name;
}

void RequirementElement::setName(const QString &name)
{
    m_name = name;
}

QString RequirementElement::component() const
{
    return m_component;
}

void RequirementElement::setComponent(const QString &component)
{
    m_component = component;
}

QString RequirementElement::module() const
{
    return m_module;
}

void RequirementElement::setModule(const QString &module)
{
    m_module = module;
}
