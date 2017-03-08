
TARGET = cintegration

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h \
    widgets/ciform.h
HEADERS += cintegrationplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp \
    widgets/ciform.cpp
SOURCES += cintegrationplugin.cpp

# Ресурсы
RESOURCES += cintegration_resources.qrc

# Дополнительные файлы
DISTFILES += cintegration.json

FORMS += \
    widgets/ciform.ui



