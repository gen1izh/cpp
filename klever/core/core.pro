# TODO: вопрос на рассмотрение (static or dynamic?)
# Сборка модуля ядра проекта
# Статическая библиотека
#
# При добавлении новых модулей/плагинов сюда добавлять доп. директив не требуется

include(../klever_software/klever_software.pri)

TEMPLATE = lib
CONFIG  += dll
QMAKE_CXXFLAGS += -std=c++11

TARGET = core

DEFINES += CORE_LIBRARY

DESTDIR = $$KLEVER_APP_PATH

# Менеджер настроек приложения
HEADERS += settings/modulespage.h \
    library/orm/db/QDjango.h \
    library/orm/db/QDjango_p.h \
    library/orm/db/QDjangoMetaModel.h \
    library/orm/db/QDjangoModel.h \
    library/orm/db/QDjangoQuerySet.h \
    library/orm/db/QDjangoQuerySet_p.h \
    library/orm/db/QDjangoWhere.h \
    library/orm/db/QDjangoWhere_p.h \
    library/orm/models/mainqdjangomodel.h \
    library/orm/models/pluginslistqdjangomodel.h \
    frameWork/status_codes.h \
    library/glabals.h \
    interfaces/itopmanager.h \
    frameWork/base.h \
    frameWork/managers.h \
    interfaces/iautorizationmanager.h \
    interfaces/isessionmanager.h \
    frameWork/managers/mock/sessionmock.h \
    frameWork/gui/klevergui.h
HEADERS += settings/optionspage.h
HEADERS += settings/appsettings.h
HEADERS += settings/modules/modulesmanager.h
HEADERS += settings/modules/modulessettingswidget.h
HEADERS += settings/modules/modulesmainwindget.h
HEADERS += settings/modules/moduleslistmodel.h

# Карскас приложения
HEADERS += frameWork/gui/iformmanager.h
HEADERS +=
HEADERS +=
HEADERS += frameWork/gui/mainwindow/mainwindow.h
HEADERS += frameWork/gui/mainwindow/mdiarea.h
HEADERS += frameWork/information.h
HEADERS +=
HEADERS += frameWork/pipe/parameter.h
HEADERS +=
HEADERS += frameWork/managers/mock/loggermock.h
HEADERS += frameWork/sysscripts/systemoperations.h

# Интерфейсы приложения
HEADERS += interfaces/iplugininterface.h
HEADERS += interfaces/moduleinterface.h
HEADERS += interfaces/managerinterface.h
HEADERS += interfaces/ilogger.h
HEADERS += interfaces/iloggermanager.h
HEADERS +=
HEADERS +=
HEADERS +=

# Библиотеки ядра
HEADERS += library/moduleThread/modulethread.h
HEADERS += library/lampLib/qlampwidget.h
HEADERS += library/setupApi/main.h
HEADERS += library/setupApi/sessions.h
HEADERS += library/setupApi/app.h
HEADERS += library/setupApi/module.h
HEADERS += library/utilsLibrary/utilslibrary.h
HEADERS += library/setupApi/isetupapi.h
HEADERS += library/databasesapi/mysql/mysqldatabaseapi.h
HEADERS += library/processDialog/processdialog.h
HEADERS += library/qled/qled.h
HEADERS += library/loggerapi/loggerapi.h
HEADERS += library/emptypage/emptypage.h
HEADERS += library/message/messagelibrary.h
HEADERS +=


# Исходники

# Менеджер настроек
SOURCES += settings/modulespage.cpp \
    frameWork/information.cpp \
    library/orm/db/QDjango.cpp \
    library/orm/db/QDjangoMetaModel.cpp \
    library/orm/db/QDjangoModel.cpp \
    library/orm/db/QDjangoQuerySet.cpp \
    library/orm/db/QDjangoWhere.cpp \
    library/orm/models/mainqdjangomodel.cpp \
    library/orm/models/pluginslistqdjangomodel.cpp \
    frameWork/base.cpp \
    frameWork/managers.cpp \
    frameWork/managers/mock/sessionmock.cpp \
    interfaces/managerinterface.cpp \
    frameWork/gui/klevergui.cpp
SOURCES += settings/optionspage.cpp
SOURCES += settings/appsettings.cpp
SOURCES += settings/modules/modulesmanager.cpp
SOURCES += settings/modules/modulessettingswidget.cpp
SOURCES += settings/modules/modulesmainwindget.cpp
SOURCES += settings/modules/moduleslistmodel.cpp

# Карскас приложения
SOURCES +=
SOURCES +=
SOURCES += frameWork/gui/mainwindow/mainwindow.cpp
SOURCES += frameWork/gui/mainwindow/creator.cpp
SOURCES += frameWork/gui/mainwindow/mdiarea.cpp
SOURCES +=
SOURCES += frameWork/pipe/parameter.cpp
SOURCES += frameWork/sysscripts/filesoperations.cpp
SOURCES +=
SOURCES +=
SOURCES +=
SOURCES +=
SOURCES += frameWork/sysscripts/systemoperations.cpp

# Карскас приложения
SOURCES +=
SOURCES += frameWork/managers/mock/loggermock.cpp

# Интерфейсы приложения
SOURCES += interfaces/iplugininterface.cpp
SOURCES += interfaces/moduleinterface.cpp

# Библиотеки ядра
SOURCES += library/moduleThread/modulethread.cpp
SOURCES += library/lampLib/qlampwidget.cpp
SOURCES += library/utilsLibrary/utilslibrary.cpp
SOURCES += library/databasesapi/mysql/mysqldatabaseapi.cpp
SOURCES += library/processDialog/processdialog.cpp
SOURCES += library/qled/qled.cpp
SOURCES += library/loggerapi/loggerapi.cpp
SOURCES += library/emptypage/emptypage.cpp
SOURCES += library/setupApi/app.cpp
SOURCES += library/message/messagelibrary.cpp
SOURCES +=

# Ресурсы
RESOURCES += frameWork/resources/framework_resources.qrc
RESOURCES += settings/cvesettingsmanager_resources.qrc
RESOURCES += library/lampLib/lamplib_resources.qrc
RESOURCES += library/qled/qled.qrc

