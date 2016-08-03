#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T10:42:44
#
#-------------------------------------------------

QT       += core gui

TARGET = genmon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dsuregisterfile.cpp \
    standartregisterformat.cpp \
    cpuregisterfile.cpp \
    tracebufferregisterfile.cpp \
    dsuproto.cpp \
    initilizerappdata.cpp \
    logger.cpp \
    ftdimodule.cpp

HEADERS  += mainwindow.h \
    dsuregisterfile.h \
    standartregisterformat.h \
    cpuregisterfile.h \
    tracebufferregisterfile.h \
    dsuproto.h \
    initilizerappdata.h \
    logger.h \
    ftdimodule.h

FORMS    += mainwindow.ui

LIBS += -L"lib" -lftd2xx

OTHER_FILES += \
    lib/ftd2xx.lib

RESOURCES += \
    icon.qrc
