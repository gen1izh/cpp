TARGET = logger

DEFINES += LOGGER_PLUGIN

include(../plugins.pri)

# Заголовочные файлы
HEADERS += \
    widgets/loggerswatcherwidget.h \
    logerscriptapi.h \
    widgets/settings/settingsform.h \
    widgets/loggerform.h \
    loggerexport.h \
    logger.h

# Исходные коды
SOURCES += \
    widgets/loggerswatcherwidget.cpp \
    logerscriptapi.cpp \
    widgets/settings/settingsform.cpp \
    widgets/loggerform.cpp \
    logger.cpp

# Ресурсы
RESOURCES += logger/logger.qrc

DISTFILES += \
    logger.json

FORMS += \
    widgets/settings/settingsform.ui \
    widgets/loggerform.ui
