TARGET = session

include(../plugins.pri)

# Заголовочные файлы
HEADERS += \
    widgets/sessionslistform.h \
    widgets/informationdialog.h \
    widgets/settings/settingwidget.h \
    widgets/addsessiondialog.h \
    widgets/models/sessionsmodel.h \
    widgets/models/sessionsqdjangomodel.h \
    sessionmanager.h

# Исходные файлы
SOURCES += \
    widgets/sessionslistform.cpp \
    widgets/informationdialog.cpp \
    widgets/settings/settingwidget.cpp \
    widgets/addsessiondialog.cpp \
    widgets/models/sessionsmodel.cpp \
    widgets/models/sessionsqdjangomodel.cpp \
    sessionmanager.cpp

# Ресурсы
RESOURCES += \
    resources.qrc

DISTFILES += \
    session.json

FORMS += \
    widgets/sessionslistform.ui \
    widgets/informationdialog.ui \
    widgets/settings/settingwidget.ui \
    widgets/addsessiondialog.ui

QMAKE_CXXFLAGS += -std=c++11
