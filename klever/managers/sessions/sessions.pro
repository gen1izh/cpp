TARGET = boot

include(../managers.pri)

# Заголовочные файлы
HEADERS += sessionmanagersettings.h
HEADERS += widgets/sessioninfodialog.h
HEADERS += widgets/sessionstable.h
HEADERS += widgets/sessionpropertydialog.h
HEADERS += rightslistmodel.h
HEADERS += sessionmanager.h

# Исходные файлы
SOURCES += sessionmanagersettings.cpp
SOURCES += widgets/sessioninfodialog.cpp
SOURCES += widgets/sessionstable.cpp
SOURCES += widgets/sessionpropertydialog.cpp
SOURCES += rightslistmodel.cpp
SOURCES += sessionmanager.cpp

# Ресурсы
RESOURCES += sessionmanager_resources.qrc

DISTFILES += boot.json
