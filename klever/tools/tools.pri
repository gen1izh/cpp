#-------------------------------------------------
#
# Project created by QtCreator 2015-02-05T15:42:17
#
#-------------------------------------------------

# Общие конфигурационные настройки для модулей/плагинов


include(../cve_software.pri)

TEMPLATE = app

DESTDIR = $$CVE_APP_PATH

QT += core gui script scripttools sql printsupport xml svg
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets printsupport webkitwidgets
}

CONFIG(debug,debug|release) {
    CVE_BUILD_DIR = $$PWD/_build/debug
} else {
    CVE_BUILD_DIR = $$PWD/_build/release
}

CVE_ROOT      = $$PWD
CVE_APP_PATH  = $$CVE_BUILD_DIR/bin/app
CVE_UT_PATH   = $$CVE_BUILD_DIR/bin/unit_tests
CVE_TEMP_PATH = $$CVE_BUILD_DIR/temp
CVE_BACKENDS_PATH = $$CVE_ROOT/modules/backends

CVE_LIBRARY_PATH = $$CVE_APP_PATH
CVE_PLUGIN_PATH  = $$CVE_APP_PATH/plugins

MOC_DIR     = $$CVE_TEMP_PATH/$$TARGET/moc
OBJECTS_DIR = $$CVE_TEMP_PATH/$$TARGET/objs
RCC_DIR     = $$CVE_TEMP_PATH/$$TARGET/qrc
UI_DIR      = $$CVE_TEMP_PATH/$$TARGET/uic

INCLUDEPATH += $$CVE_ROOT $$CVE_ROOT/core $$UI_DIR
