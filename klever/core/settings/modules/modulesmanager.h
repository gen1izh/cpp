#ifndef MODULESMANAGER_H
#define MODULESMANAGER_H

#include <QObject>

#include <interfaces/moduleinterface.h>
#include <interfaces/managerinterface.h>
#include "modulessettingswidget.h"
#include "modulesmainwindget.h"

/*!
 * \brief Структура модуля
 */
struct ModulesQueueItem {
  ModuleInterface *i;
  bool             isNeedUse;
};


/*!
 * \brief Класс менеджера модулей
 */
class ModulesManager : public QObject/*, public IManager*/
{

  Q_OBJECT


  /*!
   * \brief Конструктор
   */
  ModulesManager();

  /*!
   * \brief Копирующий конструктор
   * \param root
   */
  ModulesManager(const ModulesManager& root);
  /*!
   * \brief Конструктор присваивания
   * \return
   */
  ModulesManager& operator=(const ModulesManager&);

  /*!
   * \brief Указатель на интерфейс плагина
   */
  IPluginInterface       *mInterface;

  /*!
   * \brief Виджет списка модулей (подключение\отключение)
   */
  ModulesSettingsWidget  *_modulesSettingsWidget;

  /*!
   * \brief Виджет списка модулей (подключение\отключение)
   */
  ModulesMainWindget      *_modulesMainWidget;

  /*!
   * \brief Хеш модулей
   */
  QHash<QString,QList<ModulesQueueItem> >  _modules;

  /*!
   * Константы класса
   */
  enum {
    MODULES_COUNT_MAX = 40 // Максимально допустимое количество модулей
  };

public:

  /*!
   * \brief Instance
   * \return
   */
  static ModulesManager& instance();


  /*!
   * \brief Возвращает хеш модулей
   * \return
   */
  QHash<QString,QList<ModulesQueueItem> > modules() const {
    return _modules;
  }

  /*!
   * \brief Отключение всех виджетов и действий.
   * Это необходимо для запуска тестовых последовательностей.
   */
  void disableAllWidgetsAndActions( QHash<QString, QPair<QWidget*,QAction*> > widgetActionList,
                                    QHash<QString, QAction*> actionList);

  /*!
   * \brief Включение всех виджетов и действий.
   * Это необходимо для запуска тестовых последовательностей.
   */
  void enableAllWidgetsAndActions( QHash<QString, QPair<QWidget*,QAction*> > widgetActionList,
                                   QHash<QString, QAction*> actionList);

  /*!
   * \brief Функция загрузки плагина модуля
   * \param[in] name - Имя модуля(dll файла)
   * \param[in] id - Идентификатор модуля
   */
  void loadModule(QString name, int id);

  /*!
   * \brief Удаление всех модулей
   * При закрытии программы
   */
  void deleteAllModules();

  /*!
   * \brief Получение иконки
   * \param modname
   * \param id
   * \param widgname
   * \return
   */
  QIcon getIcon(QString modname, int id, QString widgname);

  /*!
   * \brief Получение виджета
   * \param modname
   * \param id
   * \param widgname
   * \return
   */
  QWidget *getWidget(QString modname, int id, QString widgname);

  /*!
   * \brief Получение действия
   * \param modname
   * \param id
   * \param widgname
   * \return
   */
  QAction *getAction(QString modname, int id, QString widgname);

  /*!
   * \brief Возвращает указатель на виджет настроек
   * \return
   */
  QWidget *getSettingPage();

  /*!
   * \brief Возвращает указатель на основную форму менеджера
   * \return
   */
  QWidget *getMainWindow();

  QStringList getModulesWidgetNamesStringList();
  QStringList getModulesNamesStringList();
  void updateModulesList();
  void readModulesPathAndInitialize();
public slots:
  /*!
   * \brief Инстанцирование всех модулей. Отоженная функция.
   */
  void instanceModulesLater();
  void openModulesInformationDialog(QString name, int row);

  /*!
   * \brief отключение всех модулей
   * Необходимо при запуске тестовой последоватенльости
   */
  void allModulesOff();

  /*!
   * \brief включение всех модулей
   * Необходимо при запуске тестовой последоватенльости
   */
  void allModulesOn();
};

#endif // MODULESMANAGER_H
