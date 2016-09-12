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

#endif // I_AUTORIZATION_MANAGER_H

