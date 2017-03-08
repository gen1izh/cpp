#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:42:17
#
#-------------------------------------------------

TARGET = formsManager

include(forms.pri)

LIBS += -L$$KLEVER_PLUGIN_PATH

SOURCES += formsManager.cpp \
    plug.cpp \
    pluginForms/moduleinfo/plugininformationform.cpp \
    fmopenwindowfunctions.cpp \
    pluginForms/logger/loggerswatchermdichild.cpp \
    pluginForms/moduleinfo/moduleinfomdichild.cpp \
    pluginForms/settings/settingsmdichild.cpp

HEADERS += formsManager.h \
    plug.h \
    pluginForms/moduleinfo/plugininformationform.h  \
    pluginForms/logger/loggerswatchermdichild.h  \
    pluginForms/testsequence/reportwatchermdichild.h  \
    pluginForms/moduleinfo/moduleinfomdichild.h  \
    pluginForms/settings/settingsmdichild.h

DISTFILES += formsManager.json

FORMS += \
    pluginForms/moduleinfo/plugininformationform.ui

