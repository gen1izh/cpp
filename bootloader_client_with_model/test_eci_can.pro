#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T16:31:08
#
#-------------------------------------------------

QT       += core gui

TARGET = writer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    log.cpp \
    dataoperations.cpp \
    ecicommand.cpp \
    ixxatapiwrapper.cpp \
    ackextractor.cpp \
    threadsmodule.cpp \
    model.cpp \
    ethcan_api.c \
    interfacestrategy.cpp \
    traffic.cpp \
    ixxatStrategyRelease.cpp \
    gresbStrategyRelease.cpp

HEADERS  += mainwindow.h \
    inc/ProductVersion.rh \
    inc/OsEci.h \
    inc/ECI_version.h \
    inc/ECI_pshpack8.h \
    inc/ECI_pshpack4.h \
    inc/ECI_pshpack1.h \
    inc/ECI_poppack.h \
    inc/ECI_logging.h \
    inc/ECI_lintype.h \
    inc/ECI_hwtype.h \
    inc/ECI_error.h \
    inc/ECI_cantype.h \
    inc/ECI_align.h \
    inc/ECI111.h \
    inc/ECI109.h \
    inc/ECI105.h \
    inc/ECI101.h \
    inc/ECI10E.h \
    inc/ECI10A.h \
    inc/ECI005.h \
    inc/ECI002.h \
    inc/ECI.h \
    log.h \
    dataoperations.h \
    inc/ecicommand.h \
    ixxatapiwrapper.h \
    threadsmodule.h \
    ackextractor.h \
    model.h \
    ethcan_api.h \
    traffic.h \
    gresbStrategyRelease.h \
    ixxatStrategyRelease.h \
    interfaceStrategy.h

FORMS    += mainwindow.ui


LIBS     += /usr/lib/libeci10ADriverLinux.so.1.6.1249.0
