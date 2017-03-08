
TARGET = document

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h \
    widgets/document/bf_documentsform.h \
    widgets/document/glossarydialog.h \
    widgets/document/termsdialog.h \
    ../_shared/db/models/docelement.h \
    ../_shared/db/models/glossaryelement.h \
    ../_shared/db/models/termselement.h \
    widgets/document/generators/documentgenerator.h
HEADERS += documentplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp \
    widgets/document/bf_documentsform.cpp \
    widgets/document/glossarydialog.cpp \
    widgets/document/termsdialog.cpp \
    ../_shared/db/models/docelement.cpp \
    ../_shared/db/models/glossaryelement.cpp \
    ../_shared/db/models/termselement.cpp \
    widgets/document/generators/documentgenerator.cpp
SOURCES += documentplugin.cpp

# Ресурсы
RESOURCES += document_resources.qrc \
    widgets/document/images.qrc

# Дополнительные файлы
DISTFILES += document.json

FORMS += \
    widgets/document/bf_documentsform.ui \
    widgets/document/glossarydialog.ui \
    widgets/document/termsdialog.ui



