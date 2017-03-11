
TARGET = architect

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h \
    widgets/architect/bf_architectform.h \
    widgets/architect/editarchitectelementdialog.h \
    widgets/architect/newarhitectelementdialog.h \
    ../_shared/db/models/architectelement.h \
    ../_shared/db/models/architectlinks.h \
    ../_shared/db/models/architecttypealias.h \
    widgets/architect/spoiler.h
HEADERS += architectplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp \
    widgets/architect/bf_architectform.cpp \
    widgets/architect/editarchitectelementdialog.cpp \
    widgets/architect/newarhitectelementdialog.cpp \
    ../_shared/db/models/architectelement.cpp \
    ../_shared/db/models/architectlinks.cpp \
    ../_shared/db/models/architecttypealias.cpp \
    widgets/architect/spoiler.cpp
SOURCES += architectplugin.cpp

# Ресурсы
RESOURCES += architect_resources.qrc \
    widgets/architect/images.qrc

# Дополнительные файлы
DISTFILES += architect.json

FORMS += \
    widgets/architect/bf_architectform.ui \
    widgets/architect/editarchitectelementdialog.ui \
    widgets/architect/newarhitectelementdialog.ui



