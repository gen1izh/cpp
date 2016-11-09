#
# Сборка исполняемого .exe файла
#

include(../klever_software/klever_software.pri)

TEMPLATE = app

CONFIG(debug, debug|release) {
  TARGET   = kleverd_software
} else {
  TARGET   = klever_software
}

DESTDIR += $$KLEVER_APP_PATH

LIBS += -L$$KLEVER_APP_PATH -lcore \

SOURCES += main.cpp \
    kapplication.cpp \
    singleapplication.cpp

HEADERS += \
    kapplication.h \
    singleapplication.h
