TARGET = boot

include(../managers.pri)

# Заголовочные файлы
HEADERS += \
    widgets/sessionslistform.h \
    widgets/informationdialog.h \
    widgets/settings/settingwidget.h \
    widgets/addsessiondialog.h
HEADERS +=
HEADERS += widgets/sessionstable.h
HEADERS += widgets/sessionpropertydialog.h
HEADERS +=
HEADERS += sessionmanager.h

# Исходные файлы
SOURCES += \
    widgets/sessionslistform.cpp \
    widgets/informationdialog.cpp \
    widgets/settings/settingwidget.cpp \
    widgets/addsessiondialog.cpp
SOURCES +=
SOURCES += widgets/sessionstable.cpp
SOURCES += widgets/sessionpropertydialog.cpp
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
