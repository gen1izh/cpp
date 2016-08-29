#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:42:17
#
#-------------------------------------------------

# Разработчик модуля обязательно указывает имя своего модуля через TARGET
TARGET = formsManager

# Разработчик модуля обязательно подключает pri актуальной платформы
include(frontends.pri)

# Разработчик модуля указывает подключаемые библиотеки при необходимости
# TODO: путь до headers и libs указывается в CVE_software.pri
LIBS += -L$$CVE_PLUGIN_PATH
#LIBS *= -ltemplate

# Менеджер форм и прототипы форм приложения
SOURCES += formsManager.cpp \
    modules/control/controlpowermdichild.cpp
SOURCES +=  mod.cpp
SOURCES += fmactions.cpp
SOURCES += fmconnectors.cpp
SOURCES += fmtoolbar.cpp
SOURCES += fmmenu.cpp
SOURCES += fmopenwindowfunctions.cpp
SOURCES += fmdocks.cpp
SOURCES += man.cpp
SOURCES +=
SOURCES += managers/logger/loggerswatchermdichild.cpp
SOURCES += managers/testsequence/testsequencetreemdichild.cpp
SOURCES += managers/testsequence/testsequenceexecutortreemdichild.cpp
SOURCES += managers/moduleinfo/moduleinfomdichild.cpp
SOURCES += managers/settings/settingsmdichild.cpp

# Менеджер форм и прототипы форм приложения
HEADERS += formsManager.h \
    modules/control/controlpowermdichild.h
HEADERS += mod.h
HEADERS += man.h
HEADERS +=
HEADERS += managers/logger/loggerswatchermdichild.h
HEADERS += managers/testsequence/reportwatchermdichild.h
HEADERS += managers/testsequence/testsequencetreemdichild.h
HEADERS += managers/testsequence/testsequenceexecutortreemdichild.h
HEADERS += managers/moduleinfo/moduleinfomdichild.h
HEADERS += managers/settings/settingsmdichild.h

#
DISTFILES += formsManager.json

# TODO: зачем тут ресурсы? Уже не понадобятся.
RESOURCES += \
    modules/res.qrc
