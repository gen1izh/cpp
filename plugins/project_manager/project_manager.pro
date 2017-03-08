
TARGET = project_manager
include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingsform.h
HEADERS += project_manager.h

# Исходные файлы
SOURCES += widgets/settings/settingsform.cpp
SOURCES += project_manager.cpp

# Ресурсы
RESOURCES += project_manager_resources.qrc \
    pmplugin.qrc

# Дополнительные файлы
DISTFILES += project_manager.json

FORMS += \
    widgets/settings/settingsform.ui




