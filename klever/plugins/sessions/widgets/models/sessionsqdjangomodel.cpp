#include "sessionsqdjangomodel.h"

QString Sessions::name() const
{
    return m_name;
}

void Sessions::setName(const QString &name)
{
    m_name =name;
}

QString Sessions::parameters() const
{
    return m_parameters;
}

void Sessions::setParameters(const QString &parameters)
{
    m_parameters = parameters;
}

QString Sessions::information() const
{
    return m_information;
}

void Sessions::setInformation(const QString &information)
{
    m_information = information;
}








