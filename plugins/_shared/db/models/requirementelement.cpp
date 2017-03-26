#include "requirementelement.h"


RequirementElement::RequirementElement(QObject *parent)
    : QDjangoModel(parent)
{
    setForeignKey("component", new ArchitectElement(this));
}

QString RequirementElement::type() const
{
    return m_type;
}

void RequirementElement::setType(const QString &type)
{
    m_type = type;
}

QString RequirementElement::name() const
{
    return m_name;
}

void RequirementElement::setName(const QString &name)
{
    m_name = name;
}

ArchitectElement *RequirementElement::component() const
{
    return qobject_cast<ArchitectElement *>(foreignKey("component"));
}

void RequirementElement::setComponent(ArchitectElement *component)
{
     setForeignKey("component", component);
}
