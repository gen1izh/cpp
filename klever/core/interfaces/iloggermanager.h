#ifndef ILOGGERPLUGIN_H
#define ILOGGERPLUGIN_H

#include "ilogger.h"
#include "plugininterface.h"

class ILoggerPlugin : public ILogger, public PluginInterface {

public:
    ILoggerPlugin(){}
    virtual ~ILoggerPlugin(){}
};


#define ILoggerPlugin_iid "ru.home.klever.ILoggerPlugin"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(ILoggerPlugin, ILoggerPlugin_iid)

#endif // ILOGGERPLUGIN_H

