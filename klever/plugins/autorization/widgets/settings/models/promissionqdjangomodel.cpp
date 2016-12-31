#include "promissionqdjangomodel.h"

QString Promission::name() const
{
    return m_name;
}

void Promission::setName(const QString &name)
{
    m_name =name;
}

QString Promission::signature() const
{
    return m_signature;
}

void Promission::setSignature(const QString &signature)
{
  m_signature = signature;
}
QString Promission::constant() const
{
  return m_constant;
}

void Promission::setConstant(const QString &constant)
{
  m_constant = constant;
}






