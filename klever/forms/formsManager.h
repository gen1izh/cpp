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

   /*!
   * \brief Dock журнала
   */
  QDockWidget *m_loggerDock;

  /*!
   * \brief Меню плагинов
   */
  QMenu *m_pluginsMenu;

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
 *                              Функции открытия окон
 *******************************************************************************/

    /*!
     * \brief Открытие формы информации о модулях
     */
    void openPluginInfoWindow();

    /*!
     * \brief Открытие формы настроек приложения
     */
    void openAppOptionsWindow();
    
    /*!
     * \brief Открытие формы просмотра журналов
     */
    void openLoggersWatcherWindow();

};

#endif // FORM_MANAGER_H
