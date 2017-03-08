TARGET = logger

DEFINES += LOGGER_PLUGIN

include(../plugins.pri)

# Заголовочные файлы
HEADERS += \
    logerscriptapi.h \
    widgets/settings/settingsform.h \
    widgets/loggerform.h \
    loggerexport.h \
    logger.h \
    lthread.h \
    widgets/watcherform.h \
    widgets/models/loggermodel.h \
    widgets/models/loggerqdjangomodel.h \
    widgets/wthread.h \
    widgets/models/loggersettingsmodel.h \
    widgets/models/loggersettingsqdjangomodel.h

# Исходные коды
SOURCES += \
    logerscriptapi.cpp \
    widgets/settings/settingsform.cpp \
    widgets/loggerform.cpp \
    logger.cpp \
    lthread.cpp \
    widgets/watcherform.cpp \
    widgets/models/loggermodel.cpp \
    widgets/models/loggerqdjangomodel.cpp \
    widgets/wthread.cpp \
    widgets/models/loggersettingsmodel.cpp \
    widgets/models/loggersettingsqdjangomodel.cpp

DISTFILES += \
    logger.json

FORMS += \
    widgets/settings/settingsform.ui \
    widgets/loggerform.ui \
    widgets/watcherform.ui
