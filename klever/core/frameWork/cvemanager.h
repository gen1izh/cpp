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


#include "error.h"

namespace Core {

/*!
 * \brief Класс главного менеджера над менеджерами компонентов ядра
 */
class CveManager : public QObject {

    Q_OBJECT

    CveManager() {
        setObjectName(tr("Главный менеджер"));
    }


    CveManager(const CveManager& root);
    CveManager& operator=(const CveManager&);

    QScopedPointer<IBootManager>    _ibootmanager;
    QScopedPointer<ILoggerManager>  _iloggermanager;

    /*!
     * \brief Хеш менеджеров
     */
    QHash<QString, ManagerInterface *> _managers;


public:

    static CveManager& instance();

    /*!
     * \brief Возвращает указатель на объект журнала
     * \return
     */
    ILoggerManager  *logger() const {
        if (_iloggermanager.data()==NULL) {
            //TODO: добавить QMessage сообщение отсутствия журнала
            // Создали системный журнал
        }
        return _iloggermanager.data();
    }

    /*!
     * \brief Возвращает указатель на объект загрузочного менеджера
     * \return
     */
    IBootManager  *boot() const {
        if (_ibootmanager.data()==NULL) {
            //TODO: добавить QMessage сообщение отсутствия загрузчика
            qDebug().noquote() << "Загрузчик не был корректно подключен!";
        }
        return _ibootmanager.data();
    }

    /*!
     * \brief Инициализация менеджеров
     * \return Возвращает код ошибки, если 0 - то успешно.
     */
    int loadManagers();

    /*!
     * \brief Возвращает хеш менеджеров
     * \return
     */
    QHash<QString, ManagerInterface *> managers() const {
        if (_managers.isEmpty()) {
            //TODO: добавить QMessage сообщение отсутствия менеджеров
        }
        return _managers;
    }

    /*!
     * \brief Финализация работы главного менеджера
     * \details Удаляет все менеджеры
     */
    void finalize();

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
     * \brief isManagerExist
     * \param name
     * \return
     */
    bool isManagerExist(QString name) {
        QHashIterator<QString, ManagerInterface *>  i(_managers);
        while (i.hasNext()) {
            i.next();
            if ( name == i.key() ) {
                return true;
            }
        }
        return false;
    }

    /*!
     * \brief Создание виджетов менеджеров
     */
    void createWidgets();

    /*!
     * \brief Подготовка всех менеджеров
     */
    void createActions();

    /*!
     * \brief Создание коннекторов
     */
    void createConnectors();
};

}

#endif // CVE_MANAGER_H
