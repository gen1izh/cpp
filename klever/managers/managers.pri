# Общие конфигурационные настройки для модулей/плагинов
include(../cve_software/cve_software.pri)

TEMPLATE = lib
CONFIG  += dll

DESTDIR = $$CVE_APP_PATH

LIBS += -L$$CVE_LIBRARY_PATH \
        -lcore
