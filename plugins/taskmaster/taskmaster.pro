
TARGET = taskmaster

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h
HEADERS += taskmasterplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp
SOURCES += taskmasterplugin.cpp

# Ресурсы
RESOURCES += taskmaster_resources.qrc

# Дополнительные файлы
DISTFILES += taskmaster.json



