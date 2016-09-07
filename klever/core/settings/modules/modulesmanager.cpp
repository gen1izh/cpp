#include "modulesmanager.h"
#include <QPluginLoader>
#include <QDebug>
#include <QMessageBox>
#include "../../frameWork/gui/cvegui.h"

#include <library/loggerapi/loggerapi.h>
using namespace Library::Logger;


ModulesManager &ModulesManager::instance() {
  static ModulesManager singleObject;
  return singleObject;
}


/*
 * Возвращает список названий виджетов модулей
 */
QStringList ModulesManager::getModulesWidgetNamesStringList() {
  QHashIterator<QString,QList<ModulesQueueItem> >
      i(modules());

  QStringList lst;
  lst.clear();

  while (i.hasNext()) {
    i.next();
    for ( int j = 0; j < i.value().size(); j++ ) {
      QHashIterator<QString,QPair<QWidget*,QAction*> >
           iter(i.value().at(j).i->getWidgetActionList());

      while (iter.hasNext()) {
        iter.next();
        lst << iter.key();
      }
    }
  }

  return lst;
}

/*
 * Возвращает список названий  модулей
 */
QStringList ModulesManager::getModulesNamesStringList() {
  QHashIterator<QString,QList<ModulesQueueItem> > i(modules());
  QStringList lst;

  while (i.hasNext()) {
    i.next();
    lst << (i.value().at(0).i->getModuleName());
  }

  return lst;
}

/*
 * Инициализация виджета настроек и основного виджета менеджера
 */
ModulesManager::ModulesManager() {
  setObjectName(tr("Менеджер модулей"));

  _modulesSettingsWidget = new ModulesSettingsWidget();
  _modulesSettingsWidget->setWidgetsNamesItems(
          getModulesWidgetNamesStringList()
        );

  _modulesMainWidget  = new ModulesMainWindget();

  connect(_modulesMainWidget,SIGNAL(openModulesInformationDialog(QString,int)),
          this, SLOT(openModulesInformationDialog(QString,int)));


}

/*
 * Обновить список модулей
 */
void ModulesManager::updateModulesList() {
  _modulesMainWidget->setModulesInformationList(
          getModulesNamesStringList()
        );
}

/*
 * Открытие информационного диалога по модулям
 */
void ModulesManager::openModulesInformationDialog(QString name, int row) {
  if ((row < modules().count())&&(row > -1)) {

    QHashIterator<QString,QList<ModulesQueueItem> >  i(modules());
    while (i.hasNext()) {
      i.next();
      if (0==QString::compare(name, i.value().at(0).i->getModuleName(), Qt::CaseInsensitive)) {
        if ( i.value().at(0).i->getModuleInfo() != QStringList() ) {
          _modulesMainWidget->setInfoAndChangeLog(i.value().at(0).i->getModuleInfo().at(0),
                                                  i.value().at(0).i->getModuleInfo().at(1));
          break;
        }
      }
    }
  }
  else {
    QMessageBox msgBox;
    msgBox.setText("Нет ни одного модуля!");
    msgBox.exec();
  }

}

/*
 * Отложенная подготовка модулей к работе
 */
void ModulesManager::instanceModulesLater() {
  // Подготовка модулей к работе

    QHashIterator<QString,QList<ModulesQueueItem> >  iter(_modules);
    while (iter.hasNext()) {
      iter.next();
      for (int j = 0; j < iter.value().size(); j++ ) {
        iter.value().at(j).i->setScript();
        iter.value().at(j).i->prepareModule();
        iter.value().at(j).i->exec();
      }
    }
}

/*
 * Загрузка модуля
 */
void ModulesManager::loadModule(QString name, int id) {
  QPluginLoader loader(name);
  QObject *pluginInstance = loader.instance();

  /* TODO: Если dll не существует, а в настройках сказано, что надо грузить, то
           выведет ошибку. При этом в списке дллек модуля не будет видно... */
  if (pluginInstance) {
    mInterface = qobject_cast<IPluginInterface *>(pluginInstance);
    ModuleInterface *p = mInterface->createModule(id);

    p->initializeModule();

    QString modname = p->getModuleSysName();

    ModulesQueueItem item;
    item.i = p;
    item.isNeedUse = true;
    _modules[modname].append(item);

  }
  else {
    qDebug() << "mInterface:" << loader.errorString();

    _modulesSettingsWidget->appendBugModuleName(name);
  }

  qDebug() << "Try loaded dll: " << name;
}


/*
 * Инициализация компонентов приложения и модулей
 */
void ModulesManager::readModulesPathAndInitialize() {

  /*
                           Инициализация модулей устройств
                                                                              */
  // Инициализация объектов модулей устройств


  AppSetupApi  appsetup;

  bool  ok;                         // Признак успешной конвертации, true - успешно.
  int   i = 0;                      // Итератор для прохода

  while (i < MODULES_COUNT_MAX) {
    QString dllname;
    dllname.clear();
    // Получение имени модуля
    dllname = QString(appsetup.getApplicationParam(QString("Main"),
                                                   QString("/module%1").arg(i)));

    if (dllname!="none") {
      // Получение количества устройств на данном модулей
      // Н-р для источников питания можует быть 2.
      int count = appsetup.getApplicationParam(QString("Main"),
                                               QString("/moduleCount%1").arg(i)).toInt(&ok,10);

      if (ok) {
        // Загрузка модуля и инициализация
        for (int j = 1; j <= count; j++) {
          Core::CveGui::instance().splashMessage(QString( "Инициализация модуля '%1' ...").arg(dllname));
          loadModule(dllname, j);
        }
      }
    }

    i++;
  }

}

/*
 * Выгрузка всех модулей
 */
void ModulesManager::deleteAllModules()
{
  logInfo(this,"Уничтожение всех модулей");
  QHashIterator<QString,QList<ModulesQueueItem> >  iter(_modules);
  while (iter.hasNext()) {
    iter.next();
    for (int j = 0; j < iter.value().size(); j++ ) {
      delete iter.value().at(j).i;
    }
  }
}

/*
 * Отключения работы всех модулей.
 */
void ModulesManager::allModulesOff() {
  QHashIterator<QString,QList<ModulesQueueItem> >  iter(_modules);
  while (iter.hasNext()) {
    iter.next();
    for (int j = 0; j < iter.value().size(); j++ ) {

      // TODO: Надо подумать над этим блокирование виджетов
      // Если сессия для Оператора, то в этой сессии и запрещаем оператору все,
      // кроме запуска  тестов и просмтореа телеметрии на панелях,
      // то есть кнопки, окна модулей, менеджеров для него уже будут недоступны.

      // Но запускать тесты может и глупый разработчик, поэтому необходимо сделать
      // выборочное блокирование(только элементы управления), также закрытие окон
      // модулей и менеджеров, кроме тестовой. Панели должны быть активны.
      // Также необходимо не давать разработчику во время теста менять дерево тестов.


//      disableAllWidgetsAndActions(
//            iter.value().at(j).i->getWidgetActionList(),
//            iter.value().at(j).i->getActionList() );

      iter.value().at(j).i->depareModule();
    }
  }
}

/*
 * Включение всех модулей.
 */
void ModulesManager::allModulesOn() {
  QHashIterator<QString,QList<ModulesQueueItem> >  iter(_modules);
  while (iter.hasNext()) {
    iter.next();
    for (int j = 0; j < iter.value().size(); j++ ) {

      // TODO: Надо подумать над этим блокирование виджетов
      // Если сессия для Оператора, то в этой сессии и запрещаем оператору все,
      // кроме запуска  тестов и просмтореа телеметрии на панелях,
      // то есть кнопки, окна модулей, менеджеров для него уже будут недоступны.

      // Но запускать тесты может и глупый разработчик, поэтому необходимо сделать
      // выборочное блокирование(только элементы управления), также закрытие окон
      // модулей и менеджеров, кроме тестовой. Панели должны быть активны.
      // Также необходимо не давать разработчику во время теста менять дерево тестов.

//      enableAllWidgetsAndActions(
//            iter.value().at(j).i->getWidgetActionList(),
//            iter.value().at(j).i->getActionList() );

      iter.value().at(j).i->prepareModule();
    }
  }
}

/*
 * Получение иконки
 */
QIcon ModulesManager::getIcon(QString modname, int id, QString widgname)
{
  return  (_modules[modname].at(id).i->getWidgetActionList()
                  [widgname].first->windowIcon());
}

/*
 * Получение виджета
 */
QWidget *ModulesManager::getWidget(QString modname, int id, QString widgname)
{
  return  (_modules[modname].at(id).i->getWidgetActionList()
                  [widgname].first);
}

/*
 * Получение действия
 */
QAction *ModulesManager::getAction(QString modname, int id, QString widgname)
{
  return  (_modules[modname].at(id).i->getWidgetActionList()
           [widgname].second);
}

/*
 * Возвращает виджет настроек менеджера
 */
QWidget *ModulesManager::getSettingPage()
{
  return _modulesSettingsWidget;
}

/*
 * Возвращает основной виджет менеджера
 */
QWidget *ModulesManager::getMainWindow()
{
  return _modulesMainWidget;
}


/*
 * Отключение всех виджетов и действий.
 * Это необходимо для запуска тестовых последовательностей.
 */
void ModulesManager::disableAllWidgetsAndActions(
    QHash<QString, QPair<QWidget*,QAction*> > widgetActionList,
    QHash<QString, QAction*> actionList
    ) {
  QHashIterator<QString, QPair<QWidget*,QAction*> >  iterwa(widgetActionList);
  while (iterwa.hasNext()) {
    iterwa.next();
    if ( iterwa.value().first != NULL ) {
      iterwa.value().first->setEnabled(false);

    }
    if ( iterwa.value().second != NULL ) {
      iterwa.value().second->setEnabled(false);
    }
  }

  QHashIterator<QString, QAction* >  itera(actionList);
  while (itera.hasNext()) {
    itera.next();
    if ( ((QAction*)itera.value()) != NULL) {
      ((QAction*)itera.value())->setEnabled(false);
    }
  }
}


/*
 * Включение всех виджетов и действий.
 * Это необходимо для запуска тестовых последовательностей.
 */
void ModulesManager::enableAllWidgetsAndActions(
    QHash<QString, QPair<QWidget*,QAction*> > widgetActionList,
    QHash<QString, QAction*> actionList
    ) {
  QHashIterator<QString, QPair<QWidget*,QAction*> >  iterwa(widgetActionList);
  while (iterwa.hasNext()) {
    iterwa.next();
    if ( iterwa.value().first != NULL ) {
      iterwa.value().first->setEnabled(true);

    }
    if ( iterwa.value().second != NULL ) {
      iterwa.value().second->setEnabled(true);
    }
  }

  QHashIterator<QString, QAction* >  itera(actionList);
  while (itera.hasNext()) {
    itera.next();
    if ( ((QAction*)itera.value()) != NULL) {
      ((QAction*)itera.value())->setEnabled(true);
    }
  }
}
