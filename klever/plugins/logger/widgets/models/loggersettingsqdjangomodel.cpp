#include "loggersettingsqdjangomodel.h"


QString LoggerSettingsQDjangoModel::currentLoggerName() const
{
    return m_currentLoggerName;
}

void LoggerSettingsQDjangoModel::setCurrentLoggerName(const QString &currentLoggerName)
{
    m_currentLoggerName = currentLoggerName;
}
