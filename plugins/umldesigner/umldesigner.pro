
TARGET = umldesigner

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h
HEADERS += umldesignerplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp
SOURCES += umldesignerplugin.cpp

# Ресурсы
RESOURCES += umldesigner_resources.qrc

# Дополнительные файлы
DISTFILES += umldesigner.json



