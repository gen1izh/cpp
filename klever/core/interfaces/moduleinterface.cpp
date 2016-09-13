#include "moduleinterface.h"


ModuleInterface::ModuleInterface() {

}


ModuleInterface::~ModuleInterface() {
}

/*
 * Возвращает хеш пар виджет-действие.
 */
QHash<QString, QPair<QWidget *, QAction *> >
      ModuleInterface::getWidgetActionList() const {
  return widgetActionList;
}

/*
 * Возвращает хеш действий не привязанных к виджетам.
 */
QHash<QString, QAction *> ModuleInterface::getActionList() const {
  return actionList;
}

/*
 * Возвращает идентификатор модуля.
 */
int ModuleInterface::getId() const {
  return m_id;
}

/*
 * Устанавливает идентификатор модуля.
 */
void ModuleInterface::setId(int id) {
  m_id = id;
}

/*
 * Возвращает имя модуля.
 */
QString ModuleInterface::getModuleName() const {
  return m_moduleName;
}

/*
 * Возвращает имя объекта модуля.
 */
QString ModuleInterface::getModuleObjName() const {
  return m_moduleObjectName;
}

/*
 * Возвращает внутреннее имя модуля.
 */
QString ModuleInterface::getModuleSysName() const {
  return m_moduleSystemName;
}

/*
 * Устанавливает имя модуля.
 */
void ModuleInterface::setModuleName(QString n) {
  m_moduleName = n;
}

/*
 * Устанавливает имя объекта модуля.
 */
void ModuleInterface::setModuleObjName(QString n) {
  m_moduleObjectName = n;
}

/*
 * Устанавливает внутреннее имя модуля.
 */
void ModuleInterface::setModuleSysName(QString n) {
  m_moduleSystemName = n;
}

/*
 * Возвращает содержимое информационного файла.
 */
QStringList ModuleInterface::getModuleInfo() {
  QStringList sl;

  /* TODO: дублирование кода. Как просто исправить? */

  QFile dataInfo(QString(":/%1_info_files/doc/%2").arg(getModuleSysName()).arg("INFO"));

  if(!dataInfo.open(QIODevice::ReadOnly | QIODevice::Text))
  {
      return QStringList();
  }

  QTextStream inputInfoFileStream(&dataInfo);
  sl << inputInfoFileStream.readAll();
  dataInfo.close();

  QFile dataChangeLog(QString(":/%1_info_files/doc/%2").arg(getModuleSysName()).arg("CHANGELOG"));

  if(!dataChangeLog.open(QIODevice::ReadOnly | QIODevice::Text))
  {
      return QStringList();
  }

  QTextStream inputChangeLogFileStream(&dataChangeLog);
  sl << inputChangeLogFileStream.readAll();
  dataChangeLog.close();

  return sl;
}
