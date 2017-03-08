
TARGET = plan

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h
HEADERS += planplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp
SOURCES += planplugin.cpp

# Ресурсы
RESOURCES += plan_resources.qrc

# Дополнительные файлы
DISTFILES += plan.json



