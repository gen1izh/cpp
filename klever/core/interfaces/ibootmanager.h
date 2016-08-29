#ifndef IBOOTMANAGER
#define IBOOTMANAGER

#include "iboot.h"
#include "isession.h"
#include "managerinterface.h"

/*!
 * \brief Интерфейс загрузочного менеджера
 */
class IBootManager : public IBoot, public ManagerInterface, public AccessInterface {
  public:
    IBootManager(){}
    virtual ~IBootManager(){}
    virtual bool hasRightUser(int r) = 0;
};

// TODO: Расписать зачем это
#define IBootManager_iid "ru.irz.cve_software.IBootManager"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(IBootManager, IBootManager_iid)

#endif // IBOOTMANAGER

