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
# TODO: путь до headers и libs указывается в KLEVER_software.pri
LIBS += -L$$KLEVER_PLUGIN_PATH

# Менеджер форм и прототипы форм приложения
SOURCES += formsManager.cpp \
    plug.cpp
SOURCES += fmactions.cpp
SOURCES += fmconnectors.cpp
SOURCES += fmtoolbar.cpp
SOURCES += fmmenu.cpp
SOURCES += fmopenwindowfunctions.cpp
SOURCES += fmdocks.cpp
SOURCES += pluginForms/logger/loggerswatchermdichild.cpp
SOURCES += pluginForms/testsequence/testsequencetreemdichild.cpp
SOURCES += pluginForms/testsequence/testsequenceexecutortreemdichild.cpp
SOURCES += pluginForms/moduleinfo/moduleinfomdichild.cpp
SOURCES += pluginForms/settings/settingsmdichild.cpp

# Менеджер форм и прототипы форм приложения
HEADERS += formsManager.h \
    plug.h
HEADERS += pluginForms/logger/loggerswatchermdichild.h
HEADERS += pluginForms/testsequence/reportwatchermdichild.h
HEADERS += pluginForms/testsequence/testsequencetreemdichild.h
HEADERS += pluginForms/testsequence/testsequenceexecutortreemdichild.h
HEADERS += pluginForms/moduleinfo/moduleinfomdichild.h
HEADERS += pluginForms/settings/settingsmdichild.h

DISTFILES += formsManager.json

