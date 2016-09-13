#ifndef I_AUTORIZATION_MANAGER_H
#define I_AUTORIZATION_MANAGER_H

#include "managerinterface.h"

/*!
 * \brief Интерфейс авторизации
 */
class IAutorizationManager : public ManagerInterface {

  public:
    IAutorizationManager(){}
    virtual ~IAutorizationManager(){}

    /*!
     * \brief Запуск кода авторизации
     * \return возвращает результат true - все успешно
     */
    virtual bool execute() = 0;
};

// TODO: Расписать зачем это
#define IAutorizationManager_iid "ru.home.klever.IAutorizationManager"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(IAutorizationManager, IAutorizationManager_iid)
#endif // I_AUTORIZATION_MANAGER_H

