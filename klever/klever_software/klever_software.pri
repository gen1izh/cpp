QT += core gui script scripttools sql printsupport xml svg axcontainer network concurrent
greaterThan(QT_MAJOR_VERSION, 4){
    QT += widgets printsupport
}

CONFIG(debug,debug|release) {
    KLEVER_BUILD_DIR = $$PWD/../_build/debug
} else {
    KLEVER_BUILD_DIR = $$PWD/../_build/release
}

KLEVER_ROOT      = $$PWD/../
KLEVER_APP_PATH  = $$KLEVER_BUILD_DIR/bin/app
KLEVER_UT_PATH   = $$KLEVER_BUILD_DIR/bin/unit_tests
KLEVER_TEMP_PATH = $$KLEVER_BUILD_DIR/temp
KLEVER_BACKENDS_PATH = $$KLEVER_ROOT/modules/backends

KLEVER_LIBRARY_PATH = $$KLEVER_APP_PATH
KLEVER_PLUGIN_PATH  = $$KLEVER_APP_PATH/modules

MOC_DIR     = $$KLEVER_TEMP_PATH/$$TARGET/moc
OBJECTS_DIR = $$KLEVER_TEMP_PATH/$$TARGET/objs
RCC_DIR     = $$KLEVER_TEMP_PATH/$$TARGET/qrc
UI_DIR      = $$KLEVER_TEMP_PATH/$$TARGET/uic

INCLUDEPATH += $$KLEVER_ROOT $$KLEVER_ROOT/core $$UI_DIR
