#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

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

  QString _moduleName;     // Имя модуля (н-р Модуль источника питания)
  QString _moduleObjName;  // Название объекта модуля (н-р Кросс-панель и ФКУ)
  QString _moduleSysName;  // Внутреннее имя модуля(н-р power)

  int     _id;              // Идентификатор модуля(порядковый номер)

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

    /*!
     *  \brief Конструктор класса.
     */
    ModuleInterface();
    /*!
     * \brief Виртуальный деструктор модуля
     * TODO: Уточнить необходимость здесь реализации... может "= 0"; ?
     */
    virtual ~ModuleInterface();
    /*!
     * \brief Возвращает хеш пар виджет-действие.
     * \details Это необходимо для менеджера форм.
     * Если форма в менеджере форм получается не комплексная, то
     */
    virtual QHash<QString, QPair<QWidget* ,QAction*> > getWidgetActionList() const;
    /*!
     * \brief  Возвращает хеш действий не привязанных к виджетам.
     * \details Например в ТПО действия "Запусить grmon" и "Остановить grmon"
     * не нуждаются в виджетах, но при этом выполняют какие-то действия.
     */
    virtual QHash<QString, QAction*> getActionList() const;
    /*!
     *  \brief Возвращает идентификатор модуля.
     *  \return Возвращает идентификатор модуля.
     */
    virtual int getId() const;
    /*!
     *  \brief Устанавливает идентификатор модуля.
     *  \return Устанавливает идентификатор модуля.
     */
    virtual void setId(int id);
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
    virtual QString getModuleName() const;
    /*!
     *  \brief Возвращает имя объекта модуля.
     *  \return Возвращает имя объекта модуля.
     */
    virtual QString getModuleObjName() const;
    /*!
     *  \brief Возвращает внутреннее имя модуля.
     */
    virtual QString getModuleSysName() const;
    /*!
     *  \brief Устанавливает имя модуля.
     */
    virtual void setModuleName(QString n);
    /*!
     *  \brief Устанавливает имя объекта модуля.
     *  \return Устанавливает имя объекта модуля.
     */
    virtual void setModuleObjName(QString n);
    /*!
     *  \brief Устанавливает внутреннее имя модуля.
     */
    virtual void setModuleSysName(QString n);
    /*!
     *  \brief Возвращает путь до иконки модуля.
     */
    virtual QIcon getModuleIcon() const = 0;
    /*!
     *  \brief Запускает цикл выполнения модуля.
     *  \details Для модулей устройств - запуск потока.
     * Для чего нужен поток модуля?
     * 1. Отвязка от Gui, чтобы не было зависаний (основные команды пользователя
     *  особенно задающие(setter) оборачиваются в команды и передаются в список
     *  команд потока, getter команды не обязательно помещать в список
     * (ВНИМАНИЕ! Если get команда что-то  возвращает, что влияет на другие
     * команды, значит это не get команда, и можно же назвать ее check,
     * config и т.д. зависит от фантазии разработчика) )
     * 2. Локализация работы с потоком в одном классе ModuleThread,
     * для простоты добавления\изменения правил\функций работы с потоком.
     * Согласно принципам ООП же или Вы против?
     * 3. Для будущих автоматических добавлений возможностей, без участия или с
     * минимальным участием разработчика модуля.
     * Н-р делать дамп команд и восстанавливать его.
     * 4. Задел на будущее для требования восстановления сессии работы с ПО.
     * Даже хотя бы фиктивное, все понимают что полностью восстановить нереально,
     * много аспектов, которые мешают этому, но фиктивно для отчета, можно
     * показать что хоть что-то восстанавливается. Хотя бы так.
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

#endif // MODULEINTERFACE_H
