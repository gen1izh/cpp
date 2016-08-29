include(../cve_software/cve_software.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS += \
    logger \
    sessions \
    testsequence \
    optime \
    tube \
    autorization
