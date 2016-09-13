#ifndef I_SESSION_MANAGER_H
#define I_SESSION_MANAGER_H

#include "managerinterface.h"

/*!
 * \brief Интерфейс менеджера сессий
 */
class ISessionManager : public ManagerInterface {
  public:
    ISessionManager(){}
    virtual ~ISessionManager(){}

    /*!
     * \brief Запуск кода сессий
     * \return возвращает результат true - все успешно
     */
    virtual bool execute() = 0;

};

// TODO: Расписать зачем это
#define ISessionManager_iid "ru.home.klever.ISessionManager"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(ISessionManager, ISessionManager_iid)

#endif // I_SESSION_MANAGER_H

