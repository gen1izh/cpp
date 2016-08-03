#-------------------------------------------------
#
# Project created by QtCreator 2012-09-07T23:44:26
#
#-------------------------------------------------

QT       += core gui

TARGET = atmc
TEMPLATE = app


SOURCES += main.cpp\
        at_manager_client.cpp \
    interpreter.cpp \
    at_common_cmd.cpp \
    at_service_cmd.cpp \
    at_debuger.cpp \
    utils/crc.cpp \
    utils/crcmodel.cpp \
    prt/cmd_packet.cpp \
    at_thread.cpp \
    at_registers.cpp \
    at_report.cpp \
    at_ftdi_module.cpp \
    prt/answerExtractor.cpp

HEADERS  += at_manager_client.h \
    interpreter.h \
    drv_uart/ftd2xx.h \
    macro.h \
    utils/crcmodel.h \
    utils/crc.h \
    at_common_cmd.h \
    at_service_cmd.h \
    at_debuger.h \
    prt/cmd_packet.h \
    at_thread.h \
    at_registers.h \
    at_report.h \
    at_ftdi_module.h \
    prt/answerExtractor.h

FORMS    += at_manager_client.ui

CONFIG+=qtestlib

OTHER_FILES += \
    drv_uart/ftd2xx.lib \
    script/test_user_regs.gen \
    script/test_service_cmd/test_MOV.gen \
    script/test_service_cmd/test_ADD.gen \
    script/test_service_cmd/test_OR.gen \
    script/test_service_cmd/test_AND.gen \
    script/test_service_cmd/test_CMP.gen \
    script/test_UART1_open/test_uart1_open.gen \
    script/test_uart_cmds.gen \
    script/test_UART/test_UART_GLOBAL.gen \
    script/test_BTS/test.gen \
    script/test_TIMERS/test.gen \
    script/test_UART/test_UART.gen

LIBS += -L"C:/Qt/qt-proj/AT_manager_client/drv_uart" -lftd2xx

RESOURCES += \
    res.qrc
