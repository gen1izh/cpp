QT += core gui script scripttools sql printsupport xml svg axcontainer network
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets printsupport webkitwidgets
}

CONFIG(debug,debug|release) {
    CVE_BUILD_DIR = $$PWD/../_build/debug
} else {
    CVE_BUILD_DIR = $$PWD/../_build/release
}

CVE_ROOT      = $$PWD/../
CVE_APP_PATH  = $$CVE_BUILD_DIR/bin/app
CVE_UT_PATH   = $$CVE_BUILD_DIR/bin/unit_tests
CVE_TEMP_PATH = $$CVE_BUILD_DIR/temp
CVE_BACKENDS_PATH = $$CVE_ROOT/modules/backends

CVE_LIBRARY_PATH = $$CVE_APP_PATH
CVE_PLUGIN_PATH  = $$CVE_APP_PATH/modules

MOC_DIR     = $$CVE_TEMP_PATH/$$TARGET/moc
OBJECTS_DIR = $$CVE_TEMP_PATH/$$TARGET/objs
RCC_DIR     = $$CVE_TEMP_PATH/$$TARGET/qrc
UI_DIR      = $$CVE_TEMP_PATH/$$TARGET/uic

INCLUDEPATH += $$CVE_ROOT $$CVE_ROOT/core $$UI_DIR
