#include "templatemodule.h"
#include "templatescriptsapi.h"

//#include <managers/sessionManager/sessionmanager.h>
#include <frameWork/cve.h>

//#include <managers/cveManager.h>

/*
 * Инициализация модуля.
 */
void TemplateModule::initializeModule() {


  // Присвоение название модуля. Необходимо для журналирования.
  this->setObjectName( "TEMPLATE" );

  templateApiWrapperObj = new TemplateApiWrapper();

  // Установка имени модуля
  setModuleObjName("template");
  setModuleName("template");
  setModuleSysName("template");
  /*
   *  Создание стандартных виджетов модуля
   */
  createSettingsWidget();        // виджет настроек модуля

  /*
   * Создание внутренних элементов модуля
   */
  createActions();    // Создание действий

  createWidgets();

  createMenu();       // Создание меню
  createConnectors(); // Создание коннекторов


}



/*
 * Подготовка устройств к работе
 */
bool TemplateModule::prepareModule()
{
  return true;
}


/*
 * Перевод устройств в нерабочее состояние
 */
bool TemplateModule::depareModule()
{
  return true;
}

/*
 * Установка скриптов
 */
void TemplateModule::setScript()
{
  // Создание объекта апи для движка скриптов
  TemplateScriptsApi   *scriptApi   = new TemplateScriptsApi( NULL, this );

//  // Регистрация этого объекта в движке исполнения
//  QScriptValue value = CveManager::instance().scriptEngine()->newQObject( scriptApi );

//  CveManager::instance().addToGlobalValueList(value);

//  CveManager::instance().scriptEngine()->globalObject().setProperty(
//        QString("Template"), value );

//  // Добавление строк-подсказок в редактор
//  CveManager::instance().addScriptPrompt(scriptApi->getPromptingMessages());
}


/*
 * Выполнение фоновых операций
 */
void TemplateModule::execBackgroundOperations()
{

}

/*
 *  Запускает цикл выполнения модуля. Для модулей устройств - запуск потока.
 */
void TemplateModule::exec() {
  start();
}

/*
 * Возвращает путь до иконки модуля.
 */
QIcon TemplateModule::getModuleIcon() const {
  return QIcon();
}

/*
 *  Создает окно настроек модуля.
 */
bool TemplateModule::createSettingsWidget()
{
 return true;
}

/*!
 * Возвращает виджет настроек модуля
 * Окно настроек модуля.
 */
QWidget* TemplateModule::getSettingsWidget() const
{
  return nullptr;
}

/*
 *  Возвращает виджет панели индикаторов.
 * TODO: Много условий, надо рефакторить.
 */
QWidget *TemplateModule::getIndicatorsPanelWidget()
{
  return nullptr;
}

/*
 *  Создает меню модуля.
 */
bool TemplateModule::createMenu() {
  debugMenu = new QMenu();
  if ( debugMenu == nullptr ) {
    return false;
  }

  return true;
}

/*
 *  Возвращает главное меню модуля.
 */
QMenu *TemplateModule::getMenu() const
{
 return debugMenu;
}

/*
 * Прекращение работы модуля.
 * Отключение модуля.
 */
void TemplateModule::cleanupModule()
{
  while(!isCommandsListEmpty()) {
    ;;;
  }
  // Корректный перевод потока в нерабочее состояние
  setTerminateState();
}
