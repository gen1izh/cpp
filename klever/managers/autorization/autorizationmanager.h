#ifndef AUTORIZATION_MANAGER_H
#define AUTORIZATION_MANAGER_H

#include "widgets/settings/autorizationsettingswidget.h"

/*!
 * brief    Менеджер авторизации
 * details  Менеджер определеяет группы, роли, пользователей,
 *          разрешения.
 * author  gen1izh
 * date
 */
class AutorizationManager;

#include <frameWork/base.h>
#include <interfaces/iautorizationmanager.h>

class AutorizationManager : public QObject, public IAutorizationManager, public ManagerInterface {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID ManagerInterface_iid FILE "autorization.json")
    Q_INTERFACES(ManagerInterface)

    /*!
     * brief Виджет настроек
     */
    autorizationSettings *_settings = NULL;

public:

    AutorizationManager();

    ~AutorizationManager() {
        finalize();
    }

    /*!
     * brief Создание виджетов модуля
     */
    void createWidgets();

    /*!
     * brief Возвращает виджет настроек менеджера
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
    virtual void createActions() {}

    /*!
     * \brief Созданией коннекторов
     */
    virtual void createConnectors() {}


    /*!
     * brief Деинициализация элементов менеджера
     */
    void finalize();

public slots:

};


#endif // AUTORIZATION_MANAGER_H

