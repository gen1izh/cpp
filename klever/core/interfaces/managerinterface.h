#ifndef MANAGER_INTERFACE
#define MANAGER_INTERFACE

#include <QAction>
#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>

#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include <library/orm/models/pluginslistqdjangomodel.h>

/*!
 * \brief Интерфейс менеджеров приложения
 */
class ManagerInterface {

    public:

        ManagerInterface();
        virtual ~ManagerInterface();

        /*!
         * \brief Инициализация менеджера
         * \param[in] name - имя менеджера
         * \param[in] textName - текстовое имя менеджера
         */
        void initialize(const QString &name, const QString textName);

        /*!
         * \brief Устанавливает название для менеджера
         * \param[in] name - название менеджера
         */
        void setName(const QString &name);

        /*!
         * \brief Возвращает название менеджера
         */
        QString name() const;

        /*!
         * \brief Устанавливает текстовое название для менеджера
         * \param[in] name - название менеджера
         */
        void setTextName(const QString &name);

        /*!
         * \brief Возвращает текстовое название менеджера
         */
        QString textName() const;

        /*!
         * \brief Проверка того факта, что менеджер включен
         * \return
         */
        bool isOn() const;

        /*!
         * \brief Проверка того факта, что менеджер будет доступен
         * То есть если менеджер _isDisable = true, то это означает, то что
         * все элементы управления этого менеджера будут неактивны.
         * \return
         */
        bool isDisable() const;

        /*!
         * \brief Функция отключает менеджер или включает его
         * \return
         */
        void setOnOrOff(bool flag);

        /*!
         * \brief Проверка состояния менеджера
         * Если в файле конфигурации менеджера нет, то по умолчанию он
         * считается отключенным
         */
        void checkManagerState();

        /*!
         * \brief Возвращает хеш пар виджет-действие
         */
        QHash<QString, QPair<QWidget*, QAction*> > getWidgetActionList() const;

        /*!
         * \brief Возвращает действия менеджера
         */
        QHash<QString, QAction*> getActionList() const;

        /*!
         * \brief Возвращает указатель на форму настроек
         * \return
         */
        virtual QWidget *getSettingPage() = 0;

        /*!
         * \brief Иконка для окна настроек
         * \return возвращает иконку
         */
        virtual QIcon settingIcon() = 0;

        /*!
         * \brief Создание действий
         */
        virtual void createActions() = 0;

        /*!
         * \brief Созданией коннекторов
         */
        virtual void createConnectors() = 0;

        /*!
         * \brief Создание виджетов
         */
        virtual void createWidgets() = 0;


    private:
        /*!
         * \brief Признак подключенности менеджера
         */
        bool     m_isOn;

        /*!
         * \brief Признак неактивности менеджера
         */
        bool     m_isDisable;

        /*!
         * \brief Системное название менеджера
         */
        QString  m_name;

        /*!
         * \brief Пользователькое название менеджера
         */
        QString  m_textname;

        /*!
         * \brief База данных плагинов
         */
        QSqlDatabase m_db;

    protected:

      /*!
       * \brief Действия менеджера
       * При вызове действия происходит какое-то событие, без открытия окна
       */
      QHash<QString, QAction*> actionList;


      /*!
       * \brief Хеш пар виджет-действие
       * При вызове действия открывается окно в контексте mdi пространства
       */
      QHash<QString, QPair<QWidget*, QAction*> > widgetActionList;
};


// TODO: Расписать зачем это
#define ManagerInterface_iid "ru.home.klever.ManagerInterface"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(ManagerInterface, ManagerInterface_iid)

#endif // MANAGER_INTERFACE


