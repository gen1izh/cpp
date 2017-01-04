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
    plug.cpp \
    pluginForms/moduleinfo/plugininformationform.cpp
SOURCES += fmopenwindowfunctions.cpp
SOURCES += pluginForms/logger/loggerswatchermdichild.cpp
SOURCES += pluginForms/moduleinfo/moduleinfomdichild.cpp
SOURCES += pluginForms/settings/settingsmdichild.cpp

# Менеджер форм и прототипы форм приложения
HEADERS += formsManager.h \
    plug.h \
    pluginForms/moduleinfo/plugininformationform.h
HEADERS += pluginForms/logger/loggerswatchermdichild.h
HEADERS += pluginForms/testsequence/reportwatchermdichild.h
HEADERS += pluginForms/moduleinfo/moduleinfomdichild.h
HEADERS += pluginForms/settings/settingsmdichild.h

DISTFILES += formsManager.json

FORMS += \
    pluginForms/moduleinfo/plugininformationform.ui

