include(../klever/klever_software/klever_software.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS += \
        project_manager \
        texteditor \
        analysis \
        architect \
        cintegration \
        document \
        umldesigner \
        taskmaster \
        plan
