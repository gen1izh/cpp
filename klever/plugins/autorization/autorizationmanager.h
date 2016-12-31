#ifndef AUTORIZATION_MANAGER_H
#define AUTORIZATION_MANAGER_H

#include "widgets/settings/autorizationsettingswidget.h"

/*!
 * \brief    Менеджер авторизации
 * \details  Менеджер определеяет группы, роли, пользователей,
 *          разрешения.
 * \author  gen1izh
 * \date
 */

#include <frameWork/base.h>
#include <interfaces/iautorizationmanager.h>

class AutorizationManager : public QObject, public IAutorizationManager {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID IAutorizationManager_iid FILE "autorization.json")
    Q_INTERFACES(IAutorizationManager)

    /*!
     * \brief Виджет настроек
     */
    autorizationSettings *_settings = NULL;

public:

    AutorizationManager();

    ~AutorizationManager();

    bool execute();

    /*!
     * \brief Создание виджетов модуля
     */
    void createWidgets();

    /*!
     * \brief Возвращает виджет настроек плагина
     * return
     */
    QWidget *getSettingPage();

    /*!
     * brief Возвращает иконку для настроек
     * return
     */
    QIcon settingIcon();

    /*!
     * \brief Создание действий
     */
    void createActions();

    /*!
     * \brief Созданией коннекторов
     */
    void createConnectors();


    /*!
     * \brief Деинициализация элементов плагина
     */
    void finalize();

public slots:

};


#endif // AUTORIZATION_MANAGER_H

