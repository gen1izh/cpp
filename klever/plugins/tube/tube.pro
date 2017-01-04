
TARGET = tube
include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/tubesettingswidget.h \
    widgets/settings/settingsform.h
HEADERS += tubemanager.h

# Исходные файлы
SOURCES += widgets/settings/tubesettingswidget.cpp \
    widgets/settings/settingsform.cpp
SOURCES += tubemanager.cpp

# Ресурсы
RESOURCES += tube_resources.qrc

# Дополнительные файлы
DISTFILES += tube.json

FORMS += \
    widgets/settings/settingsform.ui




