#ifndef FORM_MANAGER_H
#define FORM_MANAGER_H

/*!
 * \brief   Менеджер форм.
 * \details Данный менеджер позволяет соединить действия экшенов
 * и открытия конкретных форм, создать доки, панель быстрого запуска и галвное
 * меню. Таким образом данный менеджер формирует ГИП ПО.
 * \date    2015
 */

#include <QObject>
#include <QMdiSubWindow>
#include <QMainWindow>
#include <QToolBar>
#include <QMessageBox>

#include <frameWork/gui/iformmanager.h>
#include <frameWork/base.h>

class FormsManager : public IFormManager {

  Q_OBJECT
  Q_PLUGIN_METADATA(IID IFormManager_iid FILE "formsManager.json")
  Q_INTERFACES(IFormManager)

  // Док для журналов
  QDockWidget *loggerBottomDock;
  QDockWidget *leftDock;

  // Табы для журналов
  QTabWidget  *tabLogger;

  // Действия для открытия окон
  QAction *_controlAction;                // Управление

  QMenu *_modulesMenu;
  QMenu *_managersMenu;
  QMenu *_complexMenu;

  /*!
   * \brief Создает и возвращает dock журнала
   * \return
   */
  QDockWidget *createLoggerDock();

  /*!
   * \brief Создает и возвращает dock менеджера тестовых последовательностей
   * \return
   */
  QDockWidget *createTestsequenceManagerDock();

  /*!
   * \brief createModulesToolBar
   */
  void createModulesToolBar();

  /*!
   * \brief createManagersToolBar
   */
  void createManagersToolBar();

  /*!
   * \brief Создание главного меню модулей
   */
  void createModulesMenu();

  /*!
   * \brief Создание главного меню менеджеров
   */
  void createManagersMenu();

  /*!
   * \brief Создание действий
   */
  void createModulesActions();

  /*!
   * \brief Создание коннекторов
   */
  void createModulesConnections();

  /*!
   * \brief Создание действий
   */
  void createManagersActions();

  /*!
   * \brief Создание коннекторов
   */
  void createManagersConnections();

  /*!
   * \brief Создание действий
   */
  void createActions();

  /*!
   * \brief Создание коннекторов
   */
  void createConnections();

  public:

    FormsManager();
    ~FormsManager() {}

    /*!
     * \brief Создает меню комплесных форм
     */
    void createMenu();

    /*!
     * \brief Создает тулбар комплесных форм
     */
    void createToolBar();

    /*!
     * \brief Создает docks
     * \param[in] docksList - список docks
     */
    void createDocks(QList<QPair<QDockWidget *, QPair<int, int> > > &docksList);

  public slots:

/*******************************************************************************
 *                  Стандартные функции открытия окон
 *******************************************************************************/

    /*!
     * \brief Открытие формы информации о модулях
     */
    void openModuleInfoWindow();

    /*!
     * \brief Открытие формы настроек приложения
     */
    void openAppOptionsWindow();

/*******************************************************************************
 *                  Не стандартные функции открытия окон. Модули.
 *                  Специфичны для каждого проекта
 *******************************************************************************/

    /*!
     * \brief Открытие дочернего окна "Управления" Тестовая форма
     */
    void openControlWindow();

/*******************************************************************************
 *                  Не стандартные функции открытия окон. Менеджеры.
 *                  Специфичны для каждого проекта
 *******************************************************************************/


    /*!
     * \brief Открытие формы тестовых последовательностей
     */
    void openTestSequenceTreeWindow();

    /*!
     * \brief Открытие формы тестовых последовательностей. Исполнение.
     */
    void openTestSequenceExecutorTreeWindow();

    
    /*!
     * \brief Открытие формы просмотра журналов
     */
    void openLoggersWatcherWindow();

};

#endif // FORM_MANAGER_H
