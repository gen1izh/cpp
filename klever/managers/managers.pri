# Общие конфигурационные настройки для модулей/плагинов
include(../klever_software/klever_software.pri)

TEMPLATE = lib
CONFIG  += dll

DESTDIR = $$KLEVER_APP_PATH

LIBS += -L$$KLEVER_LIBRARY_PATH \
        -lcore
