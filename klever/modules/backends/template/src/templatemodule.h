#ifndef TEMPLATEMODULE_H
#define TEMPLATEMODULE_H

// Стандартные подключаемые библиотеки
#include <QMenu>
#include <QToolBar>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QTableWidget>
#include <QGroupBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCheckBox>
#include <QScriptValue>

#include "templateexport.h"

// Обертка над функциями библиотеки устройства
#include "wrapper/templateapiwrapper.h"
// Операции модуля источника питания


// Подключение к функциям связывающим модуль с ядром ПО КПА
#include <interfaces/moduleinterface.h>
#include <library/setupApi/module.h>
#include <library/moduleThread/modulethread.h>


// Виджеты модуля



/******************************************************************************
 *                    Класс модуля ШАБЛОН
 ******************************************************************************/
 /*!
  * \brief Класс работы с источником питания
  */
class TEMPLATE_EXPORT TemplateModule : public ModuleThread,
                                       public ModuleInterface {

  Q_OBJECT

  /*!
   * \brief Настройки модуля.
   */
  ModuleSetupApi _setting;

  /*!
   * \brief Обертка для функций библиотеки драйвера устройства.
   */
  TemplateApiWrapper*  templateApiWrapperObj;

    /*!
     * \brief indicators
     */
    QWidget         *indicators;
  public:

    /*
                        Основные функции модуля устройства
                                                                             */

    /*!
     * \brief Конструктор модуля источника питания
     * \param[in] parent указатель на родительский класс.
     */
    TemplateModule( QObject *parent = 0 );

    /*!
     * \brief Деструктор модуля источника питания.
     */
    ~TemplateModule();

    /*!
     * \brief Создание соединителей модуля.
     */
    void createConnectors();

    /*!
     * \brief Создание действий модуля.
     */
    void createActions();

    /*!
     * \brief Подготовка источника питания к работе.
     * \return состояние процесса подготовки модуля к работе.
     */
    bool prepareModule();

    /*!
     *  \brief Перевод модуля в нерабочее состояние.
     *  \details Это необходимо при запуске тестовой последовательности.
     */
    bool depareModule();


    /*!
     *  \brief Удаление элементов виджетов.
     */
    void cleanupModuleElements();

    /*!
     *  \brief Удаление виджетов.
     */
    void cleanupWidgets();

    /*
               Реализация функций интерфейса ядра ПО КПА с модулем
                                                                             */

    /*!
     *  \brief Инициализация модуля.
     *  \return Инициализация модуля.
     */
    void initializeModule();

    /*!
     *  \brief Отключение модуля.
     *  \details
     */
    void cleanupModule();

    /*!
     *  \brief Запускает цикл выполнения модуля.
     *  \details Для модулей устройств - запуск потока.
     */
    void exec();

    /*!
     *  \brief Возвращает путь до иконки модуля.
     *  \return Возвращает путь до иконки модуля.
     */
    QIcon getModuleIcon() const;

    /*!
     *  \brief Создает окно настроек модуля.
     *  \return Окно настроек модуля.
     */
    bool createSettingsWidget();

    /*!
     *  \brief Возвращает окно настроек модуля.
     *  \return Окно настроек модуля.
     */
    QWidget* getSettingsWidget() const;

    /*!
     *  \brief Возвращает виджет панели индикаторов.
     *  \return
     */
    QWidget* getIndicatorsPanelWidget();

    /*!
     * \brief getParameters
     * \return
     */
    QHash<QString, Parameter*> getParameters(){
      QHash<QString, Parameter*> h;
      return h;
    }

    /*!
     *  \brief Создает меню модуля.
     *  \return Необходимо для главного меню модуля.
     */
    bool createMenu();
    /*!
     *  \brief Возвращает главное меню модуля.
     *  \return Главное меню модуля.
     */
    QMenu* getMenu() const;
    /*!
     * \brief Функции построения специфичных виджетов.
     */
    void createWidgets();


    /*
                                 Действия
                                                                             */


    /*
                            Основное меню
                                                                             */
    /*!
     * \brief Меню для отладки виджетов.
     */
    QMenu   *debugMenu;

    /*
                            Дополнительные функции
                                                                             */

    /*!
     * \brief Возвращает указатель на объект  обертки низкоуровневых функций.
     * \return возвращает указатель.
     */


public slots:

    /*!
     * \brief Установка скриптов
     */
    void setScript();


  protected:
    /*!
     * \brief Выполнение фоновых операций.
     */
    void execBackgroundOperations();


};

#endif // TEMPLATEMODULE_H
