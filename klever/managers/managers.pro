include(../klever_software/klever_software.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS += \
    logger \
    sessions \
    tube \
    autorization
