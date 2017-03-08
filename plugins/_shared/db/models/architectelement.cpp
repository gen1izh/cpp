#include "architectelement.h"



QString ArchitectElement::article() const
{
    return m_article;
}

void ArchitectElement::setArticle(const QString &article)
{
    m_article = article;
}

QString ArchitectElement::name() const
{
    return m_name;
}

void ArchitectElement::setName(const QString &name)
{
    m_name = name;
}

QString ArchitectElement::description() const
{
    return m_description;
}

void ArchitectElement::setDescription(const QString &description)
{
    m_description = description;
}

QString ArchitectElement::parentElementType() const
{
    return m_parentElementType;
}

void ArchitectElement::setParentElementType(const QString &parentElementType)
{
    m_parentElementType = parentElementType;
}

QString ArchitectElement::parentElementArticle() const
{
    return m_parentElementArticle;
}

void ArchitectElement::setParentElementArticle(const QString &parentElementArticle)
{
    m_parentElementArticle = parentElementArticle;
}

QString ArchitectElement::type() const
{
    return m_type;
}

void ArchitectElement::setType(const QString &type)
{
    m_type = type;
}
