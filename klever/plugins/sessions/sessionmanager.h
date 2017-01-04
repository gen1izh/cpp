#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

/*!
 * \brief   Менеджер сессий
 * \date    2015
 */
#include <QObject>

#include "widgets/settings/settingwidget.h"
#include "widgets/sessionslistform.h"
#include "widgets/informationdialog.h"

#include <interfaces/isessionmanager.h>

// Подключение функций работы с настройками
#include <library/setupApi/main.h>
#include <library/setupApi/sessions.h>
#include <library/emptypage/emptypage.h>

#include <frameWork/base.h>

class SessionManager : public QObject, public ISessionPlugin
{

    Q_OBJECT

    Q_PLUGIN_METADATA(IID ISessionPlugin_iid FILE "session.json")
    Q_INTERFACES(ISessionPlugin)

    /*!
     * \brief Проверка существования каталога sessions и ini файла
     * \details Перед работой с файлом сессий, необходимо проверить его существование
     * и если он не существует, то создать.
     */
    void checkSessionContent();

    /*!
     * \brief Виджет настроек сессий
     */
    SettingWidget *m_setting = nullptr;

    /*!
     * \brief Форма сессий
     */
    SessionsListForm    *m_sessionsListForm = nullptr;

    /*!
     * \brief Диалоговое окно с информацией о сессии
     */
    InformationDialog   *m_informationDialog = nullptr;

    public:

        SessionManager();
        ~SessionManager();

        /*!
         * \brief Запуск кода загрузчика
         * \return
         */
        bool execute();

        /*!
         * \brief Проверка наличия сессий по-умолчанию
         */
        void checkDefaultSessions();

        /*!
         * \brief Создание виджетов модуля
         */
        void createWidgets();

        /*!
         * \brief Создание действий
         */
        void createActions();

        /*!
         * \brief Создание коннекторов
         */
        void createConnectors();

        /*!
         * \brief Возвращает указатель на виджет настроек
         * \return
         */
        QWidget *getSettingPage();

        /*!
         * \brief Возвращает иконку для настроек
         * \return
         */
        QIcon settingIcon();

        /*!
         * \brief Информация о плагине
         */
        QString getInformation();

        /*!
         * \brief Деинициализация элементов плагина сессии
         */
        int finalize();

};


#endif // SESSION_MANAGER_H
