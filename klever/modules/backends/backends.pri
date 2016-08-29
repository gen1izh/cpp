#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:42:17
#
#-------------------------------------------------

# Общие конфигурационные настройки для модулей/плагинов
include(../../cve_software/cve_software.pri)

TEMPLATE = lib
CONFIG  += dll

DESTDIR = $$CVE_PLUGIN_PATH

LIBS += -L$$CVE_LIBRARY_PATH \
        -lcore
