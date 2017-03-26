
TARGET = project_manager
include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/settingsform.h \
    ../_shared/db/models/architectelement.h \
    ../_shared/db/models/architectlinks.h \
    ../_shared/db/models/architecttypealias.h \
    ../_shared/db/models/comment.h \
    ../_shared/db/models/docelement.h \
    ../_shared/db/models/glossaryelement.h \
    ../_shared/db/models/imageselement.h \
    ../_shared/db/models/requirementelement.h \
    ../_shared/db/models/termselement.h
HEADERS += project_manager.h

# Исходные файлы
SOURCES += widgets/settings/settingsform.cpp \
    ../_shared/db/models/architectelement.cpp \
    ../_shared/db/models/architectlinks.cpp \
    ../_shared/db/models/architecttypealias.cpp \
    ../_shared/db/models/comment.cpp \
    ../_shared/db/models/docelement.cpp \
    ../_shared/db/models/glossaryelement.cpp \
    ../_shared/db/models/imageselement.cpp \
    ../_shared/db/models/requirementelement.cpp \
    ../_shared/db/models/termselement.cpp
SOURCES += project_manager.cpp

# Ресурсы
RESOURCES += project_manager_resources.qrc \
    pmplugin.qrc

# Дополнительные файлы
DISTFILES += project_manager.json

FORMS += \
    widgets/settings/settingsform.ui




