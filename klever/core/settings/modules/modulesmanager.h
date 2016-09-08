#ifndef MODULESMANAGER_H
#define MODULESMANAGER_H

#include <QObject>

#include <interfaces/moduleinterface.h>
#include <interfaces/managerinterface.h>
#include "modulessettingswidget.h"
#include "modulesmainwindget.h"

#include <interfaces/itopmanager.h>



namespace Core {

    /*!
     * \brief Структура модуля
     */
    struct ModulesQueueItem {
      ModuleInterface *i;
      bool             isNeedUse;
    };


    /*!
     * \brief Класс менеджера модулей
     */
    class ModulesManager : public QObject, public ITopManager
    {

      Q_OBJECT

      ModulesManager();
      ModulesManager(const ModulesManager& root);
      ModulesManager& operator=(const ModulesManager&);

      /*!
       * \brief Указатель на интерфейс плагина
       */
      IPluginInterface       *m_interface;

      /*!
       * \brief Виджет списка модулей (подключение\отключение)
       */
      ModulesSettingsWidget  *m_modulesSettingsWidget;

      /*!
       * \brief Виджет списка модулей (подключение\отключение)
       */
      ModulesMainWindget      *m_modulesMainWidget;

      /*!
       * \brief Хеш модулей
       */
      QHash<QString,QList<ModulesQueueItem> >  m_modules;

      /*!
       * Константы класса
       */
      enum {
        MODULES_COUNT_MAX = 40 // Максимально допустимое количество модулей
      };

      /*!
       * \brief Функция загрузки плагина модуля
       * \param[in] name - Имя модуля(dll файла)
       * \param[in] id - Идентификатор модуля
       */
      void loadModule(QString name, int id);

    public:

      static ModulesManager& instance();

      /*!
       * \brief Загрузка модулей
       * \return
       */
      int load();

      /*!
       * \brief Удаление всех модулей
       * При закрытии программы
       */
      int finalize();

      /*!
       * \brief Возвращает хеш модулей
       * \return
       */
      QHash<QString,QList<ModulesQueueItem> > modules() const {
        return m_modules;
      }

      /*!
       * \brief Отключение всех виджетов и действий.
       * Это необходимо для запуска тестовых последовательностей.
       */
      void disableAllWidgetsAndActions( QHash<QString, QPair<QWidget*,QAction*> > widgetActionList,
                                        QHash<QString, QAction*> actionList);

      /*!
       * \brief Включение всех виджетов и действий.
       * Это необходимо для запуска тестовых последовательностей.
       */
      void enableAllWidgetsAndActions( QHash<QString, QPair<QWidget*,QAction*> > widgetActionList,
                                       QHash<QString, QAction*> actionList);


      /*!
       * \brief Получение иконки
       * \param modname
       * \param id
       * \param widgname
       * \return
       */
      QIcon getIcon(QString modname, int id, QString widgname);

      /*!
       * \brief Получение виджета
       * \param modname
       * \param id
       * \param widgname
       * \return
       */
      QWidget *getWidget(QString modname, int id, QString widgname);

      /*!
       * \brief Получение действия
       * \param modname
       * \param id
       * \param widgname
       * \return
       */
      QAction *getAction(QString modname, int id, QString widgname);

      /*!
       * \brief Возвращает указатель на виджет настроек
       * \return
       */
      QWidget *getSettingPage();

      /*!
       * \brief Возвращает указатель на основную форму менеджера
       * \return
       */
      QWidget *getMainWindow();

      QStringList getModulesWidgetNamesStringList();

      QStringList getModulesNamesStringList();

      void updateModulesList();

    public slots:
      /*!
       * \brief Инстанцирование всех модулей. Отоженная функция.
       */
      void instanceModulesLater();

      /*!
       * \brief Открытие информационного диалога по модулям
       * \param[in] name Название модуля
       * \param[in] row строка
       */
      void openModulesInformationDialog(QString name, int row);

      /*!
       * \brief Отключение всех модулей
       * Необходимо при запуске тестовой последоватенльости
       */
      void allModulesOff();

      /*!
       * \brief Включение всех модулей
       * Необходимо при запуске тестовой последоватенльости
       */
      void allModulesOn();
    };

}

#endif // MODULESMANAGER_H
