#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T15:42:17
#
#-------------------------------------------------
include(cve_software.pri)

TEMPLATE = lib
CONFIG  += dll

DESTDIR = $$CVE_PLUGIN_PATH

LIBS += -L$$CVE_LIBRARY_PATH \
        -lcore

# Минимальный набор
QT += core gui script scripttools
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets
}
