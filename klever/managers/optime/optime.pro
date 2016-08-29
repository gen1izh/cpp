
TARGET = optime
include(../managers.pri)

# Заголовочные файлы
HEADERS += widgets/settings/optimesettingswidget.h
HEADERS += optimemanager.h

# Исходные файлы
SOURCES += widgets/settings/optimesettingswidget.cpp \
    optimemanager.cpp
SOURCES +=

# Ресурсы
RESOURCES += optime_resources.qrc

# Дополнительные файлы
DISTFILES += optime.json




