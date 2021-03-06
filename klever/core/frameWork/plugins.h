#ifndef PLUGINS_H
#define PLUGINS_H

// Библиотека утилит
#include <library/utilsLibrary/utilslibrary.h>
#include <library/message/messagelibrary.h>

// Включения для объектов-оберток модуля скриптов
#include <plugins/logger/logger.h>
#include <plugins/logger/widgets/settings/settingsform.h>

#include <settings/appsettings.h>

#include <interfaces/iloggermanager.h>
#include <interfaces/isessionmanager.h>
#include <interfaces/iautorizationmanager.h>

#include <QFileInfo>

#include <QScopedPointer>

#include "frameWork/managers/mock/sessionmock.h"
#include "frameWork/managers/mock/loggermock.h"

#include <frameWork/base.h>
#include <QTimer>

#include "status_codes.h"

#include <library/message/messagelibrary.h>

#include <interfaces/itopmanager.h>

namespace Core {

    /*!
     * \brief Класс главного плагина
     */
    class Plugins : public QObject, public ITopManager {

        Q_OBJECT

        Plugins();

        // Не переопределять!
        Plugins(const Plugins& root);
        Plugins& operator=(const Plugins&);

        // Интерфейс на загрузчик и журнал
        ISessionPlugin          *m_ibootmanager;
        ILoggerPlugin           *m_iloggermanager;
        IAutorizationManager    *m_iautorizationmanager;

        /*!
         * \brief Хеш плагинов
         */
        QHash<QString, PluginInterface *> m_plugins;

    public:

        static Plugins& instance();

        /*!
         * \brief Возвращает указатель на объект журнала
         * \return
         */
        ILoggerPlugin  *logger() const;

        /*!
         * \brief Возвращает указатель на объект загрузочного плагина
         * \return
         */
        ISessionPlugin  *boot() const;

        /*!
         * \brief  Возвращает указатель на объект плагина авторизации
         * \return
         */
        IAutorizationManager *autorization() const;

        /*!
         * \brief Инициализация плагинов системы.
         * \return Возвращает код ошибки, если 0 - то успешно.
         */
        int load();

        /*!
         * \brief Возвращает хеш плагинов
         * \return
         */
        QHash<QString, PluginInterface *> plugins() const;

        /*!
         * \brief Финализация работы главного плагина
         * \details Удаляет все плагины
         */
        int finalize();

        /*!
         * \brief Проверка наличия плагина
         * \param[in] name - название плагина
         * \return
         */
        bool isPluginExist(QString name);

        /*!
         * \brief Создание виджетов плагинов
         */
        void createWidgets();

        /*!
         * \brief Создание действий плагинов
         */
        void createActions();

        /*!
         * \brief Подготовка плагинов
         */
        void prepare();

        /*!
         * \brief Создание коннекторов
         */
        void createConnectors();

        /*!
         * \brief Подгржает список плагинов из БД
         * \return
         */
        QStringList LoadListFromDatabase();

        /*!
         * \brief Добавляем в список плагинов новый плагин
         * \return
         */
        void AddNewPluginDatabase(const QString &plugin_name);

        /*!
         * \brief Удаляем плагин из списка плагинов
         * \param plugin_name
         */
        void DeletePluginFromDatabase(const QString &plugin_name);
    };

}

#endif // PLUGINS_H
