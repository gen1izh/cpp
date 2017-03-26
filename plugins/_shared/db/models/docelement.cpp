#include "docelement.h"


DocElement::DocElement(QObject *parent)
    : QDjangoModel(parent) {

}

QString DocElement::uid() const
{
    return m_uid;
}

void DocElement::setUid(const QString &uid)
{
    m_uid = uid;
}

QString DocElement::name() const
{
    return m_name;
}

void DocElement::setName(const QString &name)
{
    m_name = name;
}

QString DocElement::type() const
{
    return m_type;
}

void DocElement::setType(const QString &type)
{
    m_type = type;
}

QString DocElement::content() const
{
    return m_content;
}

void DocElement::setContent(const QString &content)
{
    m_content = content;
}

QString DocElement::author() const
{
    return m_author;
}

void DocElement::setAuthor(const QString &author)
{
    m_author = author;
}

QString DocElement::datetime() const
{
    return m_datetime;
}

void DocElement::setDatetime(const QString &datetime)
{
    m_datetime = datetime;
}

int DocElement::version() const
{
    return m_version;
}

void DocElement::setVersion(int version)
{
    m_version = version;
}

QString DocElement::comment() const
{
    return m_comment;
}

void DocElement::setComment(const QString &comment)
{
    m_comment = comment;
}
