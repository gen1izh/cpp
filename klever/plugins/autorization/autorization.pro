
TARGET = autorization

include(../plugins.pri)

# Заголовочные файлы
HEADERS += widgets/settings/autorizationsettingswidget.h \
    widgets/settings/personaldata.h \
    widgets/settings/addgroupdialog.h \
    widgets/settings/editgroupdialog.h \
    widgets/settings/adduserdialog.h \
    widgets/settings/edituserdialog.h \
    widgets/settings/addpromissiondialog.h \
    widgets/settings/addroledialog.h \
    widgets/settings/editroledialog.h \
    widgets/settings/models/groupitem.h \
    widgets/settings/models/groupmodel.h \
    widgets/settings/models/groupqdjangomodel.h \
    widgets/settings/models/userqdjangomodel.h \
    widgets/settings/models/usermodel.h \
    widgets/settings/models/promissionqdjangomodel.h \
    widgets/settings/models/promissionmodel.h \
    widgets/settings/models/roleqdjangomodel.h \
    widgets/settings/models/rolemodel.h \
    widgets/autorizationdialog.h
HEADERS += autorizationmanager.h

# Исходные файлы
SOURCES += widgets/settings/autorizationsettingswidget.cpp \
    widgets/settings/personaldata.cpp \
    widgets/settings/addgroupdialog.cpp \
    widgets/settings/editgroupdialog.cpp \
    widgets/settings/adduserdialog.cpp \
    widgets/settings/edituserdialog.cpp \
    widgets/settings/addpromissiondialog.cpp \
    widgets/settings/addroledialog.cpp \
    widgets/settings/editroledialog.cpp \
    widgets/settings/models/groupitem.cpp \
    widgets/settings/models/groupmodel.cpp \
    widgets/settings/models/groupqdjangomodel.cpp \
    widgets/settings/models/userqdjangomodel.cpp \
    widgets/settings/models/usermodel.cpp \
    widgets/settings/models/promissionqdjangomodel.cpp \
    widgets/settings/models/promissionmodel.cpp \
    widgets/settings/models/roleqdjangomodel.cpp \
    widgets/settings/models/rolemodel.cpp \
    widgets/autorizationdialog.cpp
SOURCES += autorizationmanager.cpp

# Ресурсы
RESOURCES += autorization_resources.qrc

# Дополнительные файлы
DISTFILES += autorization.json

FORMS += \
    widgets/settings/personaldata.ui \
    widgets/settings/addgroupdialog.ui \
    widgets/settings/editgroupdialog.ui \
    widgets/settings/adduserdialog.ui \
    widgets/settings/edituserdialog.ui \
    widgets/settings/addpromissiondialog.ui \
    widgets/settings/addroledialog.ui \
    widgets/settings/editroledialog.ui \
    widgets/autorizationdialog.ui




