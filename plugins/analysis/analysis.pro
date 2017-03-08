
TARGET = analysis

CONFIG += c++11

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingswidget.h \
    widgets/analysis/bf_analizeform.h \
    widgets/analysis/newrequirementdialog.h \
    widgets/analysis/editrequirementdialog.h \
    ../_shared/db/models/architectelement.h \
    ../_shared/db/models/requirementelement.h
HEADERS += analysisplugin.h

# Исходные файлы
SOURCES += widgets/settings/settingswidget.cpp \
    widgets/analysis/bf_analizeform.cpp \
    widgets/analysis/newrequirementdialog.cpp \
    widgets/analysis/editrequirementdialog.cpp \
    ../_shared/db/models/architectelement.cpp \
    ../_shared/db/models/requirementelement.cpp
SOURCES += analysisplugin.cpp

# Ресурсы
RESOURCES += analysis_resources.qrc \
    widgets/analysis/images.qrc

# Дополнительные файлы
DISTFILES += analysis.json

FORMS += \
    widgets/analysis/bf_analizeform.ui \
    widgets/analysis/newrequirementdialog.ui \
    widgets/analysis/editrequirementdialog.ui



