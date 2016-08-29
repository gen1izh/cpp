#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:42:17
#
#-------------------------------------------------
# Разработчик модуля обязательно указывает имя своего модуля через TARGET
TARGET = template

# Баг Qt. Долно быть просто CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++1y

include(../../backends.pri)

# Макрос нужен для того чтобы сделать главный класс доступным для ядра
# Используется templateexport.h
DEFINES += TEMPLATE_PLUGIN

# Подключение библиотек
INCLUDEPATH += # ../lib
LIBS += # -L../lib
LIBS *= # -livi -lvisa32

# Библиотеки
HEADERS += ../lib/vpptype.h \
    wrapper/templateapiwrapper.h \
    templatemodule.h \
    templateplugin.h \
    templatescriptsapi.h
HEADERS += # ../lib/visatype.h
HEADERS += # ../lib/visa.h
HEADERS += # ../lib/version.h
HEADERS += # ../lib/types.h
HEADERS +=

#Исходники

SOURCES += \
    wrapper/templateapiwrapper.cpp \
    templateinterface.cpp \
    templatemodule.cpp \
    templateplugin.cpp \
    templatescriptsapi.cpp



RESOURCES += \
    ../resources/src/template.qrc

DISTFILES += \
    ../resources/src/templateModule.json


