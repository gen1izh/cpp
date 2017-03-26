#include "architectelement.h"


ArchitectElement::ArchitectElement(QObject *parent)
    : QDjangoModel(parent) {

}

int ArchitectElement::parentId() const
{
    return m_parentId;
}

void ArchitectElement::setParentId(int parentId)
{
    m_parentId = parentId;
}

QString ArchitectElement::type() const
{
    return m_type;
}

void ArchitectElement::setType(const QString &type)
{
    m_type = type;
}

QString ArchitectElement::name() const
{
    return m_name;
}

void ArchitectElement::setName(const QString &name)
{
    m_name = name;
}
