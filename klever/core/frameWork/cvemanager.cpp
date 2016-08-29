#include "CveManager.h"

#include <frameWork/cve.h>
#include <QTimer>

#include "frameWork/managers/mock/bootmock.h"
#include "frameWork/managers/mock/loggermock.h"

/*
 * Инстанцирование объекта главного менеджера над менеджерами компонентов ядра
 */
CveManager &CveManager::instance() {
  static CveManager singleObject;  
  return singleObject;
}

/*
 *  Инициализация менеджеров
 */
int CveManager::loadManagers() {

  if (!isMainIniExist()) {
    return NO_MAIN_INI_ERROR;
  }

  // Чтение перечня менеджеров из настроек
  MainSetupApi mainsetup;
  QStringList  mans = mainsetup.getListKeysMainParam(QString("managers"));
  ManagerInterface    *man;

  // Если менеджеры отсутствуют
  if (mans.size()==0) {
    _ibootmanager = new BootMock();
    man = static_cast<ManagerInterface *>(_ibootmanager);
    _managers["boot"] = man;

    _iloggermanager = new LoggerMock();
    man = static_cast<ManagerInterface *>(_iloggermanager);
    _managers["loggermock"] = man;

    return NO_MANAGERS_ERROR;
  }

  foreach (QString manName, mans) {
    CveGui::instance().splashMessage("Инициализация менеджера \" " + manName + " \" ");

    QString state = mainsetup.getMainParam(QString("managers"),manName);

    if (state == "on") {
      QPluginLoader loader(manName);
      QObject *pluginInstance = loader.instance();

      if (pluginInstance) {
        if (manName=="boot") {
          _ibootmanager = qobject_cast<IBootManager *>(pluginInstance);
          man = static_cast<ManagerInterface *>(_ibootmanager);
        }
        else if (manName=="logger") {
          _iloggermanager = qobject_cast<ILoggerManager *>(pluginInstance);
          man = static_cast<ManagerInterface *>(_iloggermanager);
        }
        else {
          man = qobject_cast<ManagerInterface *>(pluginInstance);
        }

        //TODO: boot и logger менеджеры тоже должны быть тут.
        //неоходимо проверить
        _managers[manName] = man; // Заполняем хеш менеджеров
      }
      else {
        messageLibrary msg;
        qDebug().noquote() << manName << ":" << loader.errorString();
        msg.createErrorMessage(tr(""), manName+tr(":")+loader.errorString());
        return MANAGERS_LOADING_ERROR;
      }

      qDebug().noquote() << manName << " = " << man;
    }
    else {
      if (manName=="boot") {
        _ibootmanager = new BootMock();
        man = static_cast<ManagerInterface *>(_ibootmanager);
        _managers["boot"] = man;
      }

      if (manName=="logger") {
        _iloggermanager = new LoggerMock();
        man = static_cast<ManagerInterface *>(_iloggermanager);
        _managers["loggermock"] = man;
      }
    }
  }

  return SUCCESSFUL;
}

/*
 * Финализация главного менеджера
 */
void CveManager::finalize() {
  QHashIterator<QString, ManagerInterface *>  i(_managers);
  while (i.hasNext()) {
    i.next();
    delete i.value(); // Удаление менеджера из памяти
  }
}

/*
 * Создание действий
 */
void CveManager::createActions() {
  QHashIterator<QString, ManagerInterface *>  i(_managers);
  while (i.hasNext()) {
    i.next();
    i.value()->createActions();
  }
}

/*
 * Создание коннекторов
 */
void CveManager::createConnectors() {
  QHashIterator<QString, ManagerInterface *>  i(_managers);
  while (i.hasNext()) {
    i.next();
    i.value()->createConnectors();
  }
}

/*
 * Создание виджетов для всех менеджеров
 */
void CveManager::createWidgets() {
  // Журнал должен инициализироваться самым первым.
  _managers["logger"]->createWidgets();

  QHashIterator<QString, ManagerInterface *>  i(_managers);
  while (i.hasNext()) {
    i.next();
    if (i.key()!="logger") {
      i.value()->createWidgets();
    }
  }
}
