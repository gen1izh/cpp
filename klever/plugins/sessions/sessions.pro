TARGET = session

include(../managers.pri)

# Заголовочные файлы
HEADERS += \
    widgets/sessionslistform.h \
    widgets/informationdialog.h \
    widgets/settings/settingwidget.h \
    widgets/addsessiondialog.h \
    widgets/models/sessionsmodel.h \
    widgets/models/sessionsqdjangomodel.h
HEADERS +=
HEADERS +=
HEADERS +=
HEADERS +=
HEADERS += sessionmanager.h

# Исходные файлы
SOURCES += \
    widgets/sessionslistform.cpp \
    widgets/informationdialog.cpp \
    widgets/settings/settingwidget.cpp \
    widgets/addsessiondialog.cpp \
    widgets/models/sessionsmodel.cpp \
    widgets/models/sessionsqdjangomodel.cpp
SOURCES +=
SOURCES +=
SOURCES +=
SOURCES +=
SOURCES += sessionmanager.cpp

# Ресурсы
RESOURCES += sessionmanager_resources.qrc

DISTFILES += \
    session.json

FORMS += \
    widgets/sessionslistform.ui \
    widgets/informationdialog.ui \
    widgets/settings/settingwidget.ui \
    widgets/addsessiondialog.ui

QMAKE_CXXFLAGS += -std=c++11
