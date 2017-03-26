
TARGET = texteditor

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h \
    widgets/texteditor/highlight/highlighter.h \
    ../_shared/db/models/docelement.h \
    ../_shared/db/models/imageselement.h \
    ../_shared/db/models/glossaryelement.h \
    ../_shared/db/models/requirementelement.h \
    ../_shared/db/models/termselement.h \
    widgets/texteditor/editorform.h \
    ../_shared/db/models/architectelement.h
HEADERS += texteditorplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp \
    widgets/texteditor/highlight/highlighter.cpp \
    ../_shared/db/models/docelement.cpp \
    ../_shared/db/models/imageselement.cpp \
    ../_shared/db/models/glossaryelement.cpp \
    ../_shared/db/models/requirementelement.cpp \
    ../_shared/db/models/termselement.cpp \
    widgets/texteditor/editorform.cpp \
    ../_shared/db/models/architectelement.cpp
SOURCES += texteditorplugin.cpp

# Ресурсы
RESOURCES += texteditor_resources.qrc \
    widgets/texteditor/images.qrc

# Дополнительные файлы
DISTFILES += texteditor.json

FORMS = widgets/texteditor/editorform.ui



