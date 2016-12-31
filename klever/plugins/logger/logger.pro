TARGET = logger

DEFINES += LOGGER_PLUGIN

include(../plugins.pri)

# Заголовочные файлы
HEADERS += cveLogger.h \
    widgets/loggerswatcherwidget.h \
    logerscriptapi.h
HEADERS += widgets/loggerstabswidgets.h
HEADERS += logger/logger.h
HEADERS += logger/customfiltertablemodel.h
HEADERS += logger/customfilteritemdelegate.h
HEADERS += logger/customfilterdialog.h
HEADERS += logger/iloggerstorage.h
HEADERS += logger/filestorage.h
HEADERS += logger/logtablemodel.h
HEADERS += logger/loggerssettingspage.h
HEADERS += logger/loggerdata.h
HEADERS += loggerexport.h

# Исходные коды
SOURCES += cveLogger.cpp \
    widgets/loggerswatcherwidget.cpp \
    logerscriptapi.cpp
SOURCES += widgets/loggerstabswidgets.cpp
SOURCES += logger/customfiltertablemodel.cpp
SOURCES += logger/customfilteritemdelegate.cpp
SOURCES += logger/customfilterdialog.cpp
SOURCES += logger/filestorage.cpp
SOURCES += logger/logtablemodel.cpp
SOURCES += logger/loggerssettingspage.cpp
SOURCES += logger/loggerdata.cpp
SOURCES += logger/logger.cpp

# Ресурсы
RESOURCES += logger/logger.qrc

DISTFILES += \
    logger.json
