#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:42:17
#
#-------------------------------------------------

# Общие конфигурационные настройки для модулей/плагинов


include(../../klever_software/klever_software.pri)

TEMPLATE = lib
CONFIG  += dll

DESTDIR = $$KLEVER_PLUGIN_PATH

LIBS += -L$$KLEVER_LIBRARY_PATH \
        -lcore
