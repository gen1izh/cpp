#include "loggerqdjangomodel.h"

QString LoggerQDjangoModel::source() const
{
    return m_source;
}

void LoggerQDjangoModel::setSource(const QString &source)
{
    m_source = source;
}

QString LoggerQDjangoModel::datetime() const
{
    return m_datetime;
}

void LoggerQDjangoModel::setDatetime(const QString &datetime)
{
    m_datetime = datetime;
}

QString LoggerQDjangoModel::txt() const
{
    return m_txt;
}

void LoggerQDjangoModel::setTxt(const QString &txt)
{
    m_txt = txt;
}

QString LoggerQDjangoModel::type() const
{
    return m_type;
}

void LoggerQDjangoModel::setType(const QString &type)
{
    m_type = type;
}
