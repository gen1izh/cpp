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
    widgets/watcherform.h

# Исходные коды
SOURCES += \
    logerscriptapi.cpp \
    widgets/settings/settingsform.cpp \
    widgets/loggerform.cpp \
    logger.cpp \
    lthread.cpp \
    widgets/watcherform.cpp

DISTFILES += \
    logger.json

FORMS += \
    widgets/settings/settingsform.ui \
    widgets/loggerform.ui \
    widgets/watcherform.ui
