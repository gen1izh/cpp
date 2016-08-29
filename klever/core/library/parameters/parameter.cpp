#include "parameter.h"

Parameter::Parameter(const QString &name, QObject *parent)
  : QObject(parent)
{
  setObjectName(name);
}

QVariant Parameter::getValue() const
{
  QReadLocker readLocker(&_valueLock);
  return _value;
}

void Parameter::setValue(const QVariant &value)
{
  _valueLock.lockForWrite();
  _value = value;
  _valueLock.unlock();
  emit valueChanged(value);
}

