#ifndef PLUGIN_INTERFACE
#define PLUGIN_INTERFACE

#include <QAction>
#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>

#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>

#include <library/orm/models/pluginslistqdjangomodel.h>

/*!
 * \brief Интерфейс плагинов приложения
 */
class PluginInterface {

    public:

        PluginInterface();
        virtual ~PluginInterface();

        /*!
         * \brief Инициализация плагина
         * \param[in] name - имя плагина
         * \param[in] textName - текстовое имя плагина
         */
        void initialize(const QString &name, const QString textName);

        /*!
         * \brief Устанавливает название для плагина
         * \param[in] name - название плагина
         */
        void setName(const QString &name);

        /*!
         * \brief Возвращает название плагина
         */
        QString name() const;

        /*!
         * \brief Устанавливает текстовое название для плагина
         * \param[in] name - название плагина
         */
        void setTextName(const QString &name);

        /*!
         * \brief Возвращает текстовое название плагина
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
         * все элементы управления этого плагина будут неактивны.
         * \return
         */
        bool isDisable() const;

        /*!
         * \brief Функция отключает менеджер или включает его
         * \return
         */
        void setOnOrOff(bool flag);

        /*!
         * \brief Проверка состояния плагина
         * Если в файле конфигурации плагина нет, то по умолчанию он
         * считается отключенным
         */
        void checkManagerState();

        /*!
         * \brief Возвращает хеш пар виджет-действие
         */
        QHash<QString, QPair<QWidget*, QAction*> > getWidgetActionList() const;

        /*!
         * \brief Возвращает действия плагина
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

        /*!
         * \brief Информация о плагине
         */
        virtual QString getInformation() = 0;


    private:
        /*!
         * \brief Признак подключенности плагина
         */
        bool     m_isOn;

        /*!
         * \brief Признак неактивности плагина
         */
        bool     m_isDisable;

        /*!
         * \brief Системное название плагина
         */
        QString  m_name;

        /*!
         * \brief Пользователькое название плагина
         */
        QString  m_textname;

        /*!
         * \brief База данных плагинов
         */
        QSqlDatabase m_db;

    protected:

      /*!
       * \brief Действия плагина
       * При вызове действия происходит какое-то событие, без открытия окна
       */
      QHash<QString, QAction*> actionList;


      /*!
       * \brief Хеш пар виджет-действие
       * При вызове действия открывается окно в контексте mdi пространства
       */
      QHash<QString, QPair<QWidget*, QAction*> > widgetActionList;
};


#define PluginInterface_iid "ru.home.klever.PluginInterface"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif // PLUGIN_INTERFACE


