#ifndef IFORMMANAGER
#define IFORMMANAGER

#include <QObject>
#include <QAction>
#include <QList>
#include <QMenuBar>
#include <QString>
#include <QIcon>
#include <QDockWidget>
#include <interfaces/plugininterface.h>

/*!
 * \brief Интерфейс плагина форм
 */
class IFormManager : public QObject {

  Q_OBJECT

  public:
    /*!
     * \brief Виртуальный деструктор интерфейса
     */
    virtual ~IFormManager(){ }

    /*!
     * \brief Функция создания меню
     * \param[in] menuBar указатель на меню-панель в главном окне приложения
     */
    virtual void createMenu() = 0;
    /*!
     * \brief Функция создания тулбара
     */
    virtual void createToolBar() = 0;
    /*!
     * \brief Функция создания доков
     */
    virtual void createDocks(QList<QPair<QDockWidget*,QPair<int,int> > > &docksList) = 0;

  public slots:

    /*!
     * \brief Открытие формы информации о модулях
     */
    virtual void openModuleInfoWindow() = 0;

    /*!
     * \brief Открытие формы настроек приложения
     */
    virtual void openAppOptionsWindow() = 0;

};

// Идентификатор класса IFormManager. Уникальный идентификатор.
#define IFormManager_iid "ru.home.klever.IFormManager"

// Использование макроса Q_DECLARE_INTERFACE для того чтобы сказать метообъектной системе Qt
// об интерфейсе
Q_DECLARE_INTERFACE(IFormManager, IFormManager_iid)


#endif // IFORMMANAGER

