#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T15:42:17
#
#-------------------------------------------------
include(cve_software.pri)

TEMPLATE = app

DESTDIR = $$CVE_UT_PATH

LIBS += -L$$CVE_LIBRARY_PATH \
        -lcore

QT += testlib
