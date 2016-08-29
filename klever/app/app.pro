#
# Сборка исполняемого .exe файла
#

include(../cve_software/cve_software.pri)

TEMPLATE = app

CONFIG(debug, debug|release) {
  TARGET   = cved_software
} else {
  TARGET   = cve_software
}

DESTDIR += $$CVE_APP_PATH

LIBS += -L$$CVE_APP_PATH -lcore \

SOURCES += main.cpp
