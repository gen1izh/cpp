#include <stdlib.h>

#include "templatemodule.h"
#include "templatescriptsapi.h"
/* Ядро */
#include <frameWork/cve.h>
//#include <managers/sessionManager/sessionmanager.h>


/*
 * Конструктор класса модуля источника питания
 */
TemplateModule::TemplateModule( QObject *parent )
{
  Q_UNUSED(parent);
  // По-умолчанию выставляем идентификатор равным 1
  setId(1);
  // Включил журнал. Теперь события будут журналироваться.
  //CveLogger::core().onLogging();



  _setting.checkModuleParam( QString( "template" ),
                    QString( "/Module Name"),
                    QString( "Модуль ШАБЛОН" ));

  indicators = nullptr;

  debugMenu = nullptr;
}

/*
 * Деструктор класса модуля источника питания
 */
TemplateModule::~TemplateModule() {
  // Остановка работы потока
  cleanupModule();
  // Удаление внутренних элементов модуля
  cleanupModuleElements();
  // Удаление всех виджетов модуля
  cleanupWidgets();
}

/*
 * Удаление элементов виджетов.
 */
void TemplateModule::cleanupModuleElements() {

  delete debugMenu;
}

/*
 * Удаление виджетов.
 */
void TemplateModule::cleanupWidgets() {
  /*
   * TODO:
   * Нужно пройтись по хешу и удалить все виджеты
   */
}

/*
                       Внутренние элементы модуля
                                                                         */

/*
 * Создание действий
 */
void TemplateModule::createActions()
{

}


/*
 * Создание виджета индикатора напряжения и тока
 */
void TemplateModule::createWidgets()
{

}

/*
 * Создание соединений сигналов-слотов
 */
void TemplateModule::createConnectors()
{

}


/*
                       Операции-обработчики сигналов
                                                                         */


/*
                     Нестандартные виджеты модуля
                                                                         */

