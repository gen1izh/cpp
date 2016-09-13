#ifndef I_LOGGER_MANAGER_H
#define I_LOGGER_MANAGER_H

#include "ilogger.h"
#include "managerinterface.h"

class ILoggerManager : public ILogger, public ManagerInterface {

public:
    ILoggerManager(){}
    virtual ~ILoggerManager(){}
};


// TODO: Расписать зачем это
#define ILoggerManager_iid "ru.irz.cve_software.ILoggerManager"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(ILoggerManager, ILoggerManager_iid)

#endif // I_LOGGER_MANAGER_H

