#ifndef CVE_MANAGER_H
#define CVE_MANAGER_H

// Библиотека утилит
#include <library/utilsLibrary/utilslibrary.h>
#include <library/message/messagelibrary.h>

// Включения для объектов-оберток модуля скриптов
#include <managers/logger/logger/logger.h>
#include <managers/logger/logger/loggerssettingspage.h>

#include <settings/appsettings.h>

#include <interfaces/iloggermanager.h>
#include <interfaces/ibootmanager.h>
#include <interfaces/moduleinterface.h>

#include <settings/modules/modulesmanager.h>

#include <QFileInfo>

#include <QScopedPointer>

#include "frameWork/managers/mock/bootmock.h"
#include "frameWork/managers/mock/loggermock.h"

#include <frameWork/base.h>
#include <QTimer>

#include "status_codes.h"

#include <library/message/messagelibrary.h>

#include <interfaces/itopmanager.h>

namespace Core {

    /*!
     * \brief Класс главного менеджера
     */
    class CveManager : public QObject, public ITopManager {

        Q_OBJECT

        CveManager();

        // Не переопределять!
        CveManager(const CveManager& root);
        CveManager& operator=(const CveManager&);

        // Интерфейс на загрузчик и журнал
        QScopedPointer<IBootManager>    _ibootmanager;
        QScopedPointer<ILoggerManager>  _iloggermanager;

        /*!
         * \brief Хеш менеджеров
         */
        QHash<QString, ManagerInterface *> m_managers;

    public:

        static CveManager& instance();

        /*!
         * \brief Возвращает указатель на объект журнала
         * \return
         */
        ILoggerManager  *logger() const;

        /*!
         * \brief Возвращает указатель на объект загрузочного менеджера
         * \return
         */
        IBootManager  *boot() const;

        /*!
         * \brief Инициализация менеджеров
         * \return Возвращает код ошибки, если 0 - то успешно.
         */
        int load();

        /*!
         * \brief Возвращает хеш менеджеров
         * \return
         */
        QHash<QString, ManagerInterface *> managers() const;

        /*!
         * \brief Финализация работы главного менеджера
         * \details Удаляет все менеджеры
         */
        int finalize();

        /*!
         * \brief Возвращает признак существования файла main.ini
         * \return
         */
        bool isMainIniExist() {
            QString path = QString("%1\\%2").arg(QDir::currentPath()).arg("main.ini");
            QFileInfo fil(path);
            if (!fil.exists()) {
                messageLibrary msg;
                msg.createErrorMessage(tr("Главный менеджер"),
                                       tr("Конфигурационный файл main.ini не найден! "
                                          "Попробуйте запустить конфигуратор и создать main.ini."));
                return false;
            }
            return true;
        }

        /*!
         * \brief Проверка наличия менеджера
         * \param[in] name - название менеджера
         * \return
         */
        bool isManagerExist(QString name);

        /*!
         * \brief Создание виджетов менеджеров
         */
        void createWidgets();

        /*!
         * \brief Создание действий менеджеров
         */
        void createActions();

        /*!
         * \brief Создание коннекторов
         */
        void createConnectors();
    };

}

#endif // CVE_MANAGER_H
