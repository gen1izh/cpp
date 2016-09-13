#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QToolBar>
#include <QList>
#include <QMap>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QHash>

#include <library/parameters/parameter.h>
#include "iplugininterface.h"

/*!
 *  \brief Абстрактный класс, реализующий общий интерфейс для модулей.
 */
class ModuleInterface {

    QString m_moduleName;           // Имя модуля
    QString m_moduleObjectName;     // Название объекта модуля
    QString m_moduleSystemName;     // Внутреннее имя модуля

    int     m_id;              // Идентификатор модуля(порядковый номер)

protected:
    /*!
     * \brief Хеш пар виджет-действие.
     */
    QHash<QString, QPair<QWidget*, QAction*> > widgetActionList;
    /*!
     * \brief  Хеш действий.
     */
    QHash<QString, QAction*> actionList;

public:


    ModuleInterface();

    virtual ~ModuleInterface();
    /*!
     * \brief Возвращает хеш пар виджет-действие.
     * \details Это необходимо для менеджера форм.
     * Если форма в менеджере форм получается не комплексная, то
     */
    QHash<QString, QPair<QWidget* ,QAction*> > getWidgetActionList() const;
    /*!
     * \brief  Возвращает хеш действий не привязанных к виджетам.
     * \details Например в ТПО действия "Запусить grmon" и "Остановить grmon"
     * не нуждаются в виджетах, но при этом выполняют какие-то действия.
     */
    QHash<QString, QAction*> getActionList() const;
    /*!
     *  \brief Возвращает идентификатор модуля.
     *  \return Возвращает идентификатор модуля.
     */
    int getId() const;
    /*!
     *  \brief Устанавливает идентификатор модуля.
     *  \return Устанавливает идентификатор модуля.
     */
    void setId(int id);
    /*!
     *  \brief Инициализация модуля.
     *  \return Инициализация модуля.
     *  В этой функции происходит инициализация виджетов и подготовка модуля
     *  к работе. Подготовка в виде инициализации виджетов, действий, коннекторов
     *  и т.д.
     */
    virtual void initializeModule() = 0;
    /*!
     *  \brief Подготовка модуля к работе.
     *  \details Подготовительная работа для запуска устройства.
     *  Если модуль устройства, значит настраивается устройство и стартует.
     */
    virtual bool prepareModule() = 0;
    /*!
     *  \brief Перевод модуля в нерабочее состояние.
     *  \details Это необходимо при запуске тестовой последовательности.
     */
    virtual bool depareModule() = 0;
    /*!
     *  \brief Деактивация модуля.
     *  \details Тут должен производится перевод модуля в нерабочее состояние
     *  с последующей остановкой потока модуля.
     */
    virtual void cleanupModule() = 0;
    /*!
     *  \brief Установка скриптовых функция на модуль.
     */
    virtual void setScript() = 0;

    /*!
     *  \brief Возвращает имя модуля.
     */
    QString getModuleName() const;
    /*!
     *  \brief Возвращает имя объекта модуля.
     *  \return Возвращает имя объекта модуля.
     */
    QString getModuleObjName() const;
    /*!
     *  \brief Возвращает внутреннее имя модуля.
     */
    QString getModuleSysName() const;
    /*!
     *  \brief Устанавливает имя модуля.
     */
    void setModuleName(QString n);
    /*!
     *  \brief Устанавливает имя объекта модуля.
     *  \return Устанавливает имя объекта модуля.
     */
    void setModuleObjName(QString n);
    /*!
     *  \brief Устанавливает внутреннее имя модуля.
     */
    void setModuleSysName(QString n);
    /*!
     *  \brief Возвращает путь до иконки модуля.
     */
    virtual QIcon getModuleIcon() const = 0;
    /*!
     *  \brief Запускает цикл выполнения модуля.
     *  \details Для модулей устройств - запуск потока.
     */
    virtual void exec() = 0;
    /*!
     *  \brief Создает окно настроек модуля.
     *  \return Окно настроек модуля.
     */
    virtual bool createSettingsWidget() = 0;
    /*!
     *  \brief Возвращает окно настроек модуля.
     *  \return Окно настроек модуля.
     */
    virtual QWidget* getSettingsWidget() const = 0;
    /*!
     *  \brief Возвращает виджет панели индикаторов.
     *  \return Окно настроек модуля.
     */
    virtual QWidget* getIndicatorsPanelWidget() = 0;
    /*!
     *  \brief Создает меню модуля.
     *  \return Необходимо для главного меню модуля.
     */
    virtual bool createMenu() = 0;
    /*!
     *  \brief Возвращает главное меню модуля.
     *  \return Главное меню модуля.
     */
    virtual QMenu* getMenu() const = 0;
    /*!
     *  \brief Возвращает содержимое информационного файла.
     *  \return
     *  Название должно быть таким (":/%1_info_files/doc/%2")
     *  н-р power_info_files/doc/INFO. То есть название ресурса должно быть
     *  осмысленным.
     */
    QStringList getModuleInfo();
};

#endif // MODULE_INTERFACE_H
