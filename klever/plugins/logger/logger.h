#ifndef LOGGER_H
#define LOGGER_H

/*!
 * \brief   Плагин журналирования.
 * \details Журнал должен быть в любом приложении. Плагин журналирования обеспечивает
 * набор функций, позволяющих работать с различными журналами.
 * Плагин журналирования реализует интерфейс <i><b>ILoggerManager</b></i>. Для разных приложения будет
 * разный журнал, сделать универсальный, много функциональный невозможно, поэтому
 * <i><b>ILogger</b></i> интерфейс содержит только одну функцию <i><b>log</b></i>. Всю остальную всю остальную
 * нагрузку по журналированию берет на себя разработчик модуля или плагина.
 * Разработчик плагина или модуля будет обращаться к Плагину журналирования через
 * главный Плагин <i><b>CveManager</b></i> и использовать функцию log, для этого в своем плагине
 * разработчик должен позаботиться о создании класс-обертки этой функции, для того
 * чтобы было удобней вести журналирование.
 *
 */

#include <QDockWidget>

// Подключаемые компоненты
#include <interfaces/iloggermanager.h>
#include "loggerexport.h"
#include "logerscriptapi.h"

#include "widgets/settings/settingsform.h"
#include "widgets/loggerform.h"
#include "widgets/watcherform.h"
#include "lthread.h"

/*!
 * \brief Класс плагина журналирования
 */
class Logger : public QObject, public ILoggerPlugin {

    Q_OBJECT

    Q_PLUGIN_METADATA(IID ILoggerPlugin_iid FILE "logger.json")
    Q_INTERFACES(ILoggerPlugin)


    /*!
     * \brief Класс настроек журналов
     */
    SettingsForm *m_settings;

    /*!
     * \brief Действия для открытия просмотрщика журналов
     */
    QAction *m_watcherAction;

    /*!
     * \brief Указатель на обретку журнала- скриптапи
     */
    LogerScriptApi *m_scripts;

    /*!
     * \brief Поток журналирования
     */
    LThread    *m_thread;

public:

    Logger();

    ~Logger();

    /*!
     * \brief Возвращает указатель на форму настроек
     * \return
     */
    QWidget *settingPage();

    /*!
     * \brief Создание виджетов плагина
     */
    void createWidgets();

    /*!
     * \brief
     */
    void createActions();

    /*!
     * \brief
     */
    void createConnectors();

    /*!
     * \brief Информация о плагине
     */
    QString information();

    /*!
     * \brief Возвращает иконку для настроек
     * \return
     */
    QIcon settingIcon();


    /*
                      Функции журналирования для устройств
                                                                        */

    /*!
     * \brief Функция журналирования сообщения
     * \param[in] ptr  - указатель на объект источник сообщения
     * \param[in] txt  - текст сообщения
     * \param[in] type - тип сообщения
     * \param[in] loggertype - тип журнала
     */
    void log(QObject *ptr,
             const QString &datetime,
             const QString &txt,
             MessagesTypes type);

public slots:
    void drawMessage(const QString &msg);
};

#endif // LOGGER_H
