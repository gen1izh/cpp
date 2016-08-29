TARGET = testsequence

include(../managers.pri)

CONFIG+=c++11

# Заголовочные файлы
HEADERS += cveTestSequences.h \
    widgets/settings/settingswidget.h \
    widgets/testsviewer/testsequencetestsviewer.h \
    widgets/testsviewer/renametestdialog.h \
    widgets/testsviewer/filesystemscriptstreemodel.h \
#    widgets/executor/testsequenceexecutorwidget.h \
    widgets/editor/testsequenceeditor.h \
    widgets/editor/testsequenceeditortreeitem.h \
    widgets/editor/testsequenceeditortreemodel.h \
    widgets/editor/testcaseeditordialog.h \
    widgets/editor/testsequencesavedialog.h \
    widgets/editor/delegate/richtextdelegate.h \
    widgets/editor/delegate/richtextlineedit.h \
    widgets/executor/testsequenceexecutor.h \
    widgets/executor/testsequenceexecutorwidget.h \
    widgets/executor/testsequenceexecutortreeitem.h \
    widgets/executor/testsequenceexecutortreemodel.h \
    widgets/executor/report/htmlrep/htmlreport.h \
    widgets/executor/testsequencedebugger.h \
    testsequencescriptapi.h \
    widgets/executor/report/reportmodel.h \
    widgets/executor/report/reporttreeitem.h \
    widgets/executor/chooseserialnumberdialog.h \
    widgets/executor/report/reportupdatethread.h

# Исходные коды
SOURCES += cveTestSequences.cpp \
    widgets/settings/settingswidget.cpp \
    widgets/testsviewer/testsequencetestsviewer.cpp \
    widgets/testsviewer/renametestdialog.cpp \
#    widgets/executor/testsequenceexecutorwidget.cpp \
    widgets/editor/testsequenceeditor.cpp \
    widgets/editor/testsequenceeditortreemodel.cpp \
    widgets/editor/testsequenceeditortreeitem.cpp \
    widgets/editor/testcaseeditordialog.cpp \
    widgets/editor/testsequencesavedialog.cpp \
    widgets/testsviewer/filesystemscriptstreemodel.cpp \
    widgets/editor/delegate/richtextlineedit.cpp \
    widgets/editor/delegate/richtextdelegate.cpp \
    widgets/executor/testsequenceexecutor.cpp \
    widgets/executor/testsequenceexecutorwidget.cpp \
    widgets/executor/testsequenceexecutortreeitem.cpp \
    widgets/executor/testsequenceexecutortreemodel.cpp \
    widgets/executor/report/htmlrep/htmlreport.cpp \
    widgets/executor/testsequencedebugger.cpp \
    testsequencescriptapi.cpp \
    widgets/executor/report/reportmodel.cpp \
    widgets/executor/report/reporttreeitem.cpp \
    widgets/executor/chooseserialnumberdialog.cpp \
    widgets/executor/report/reportupdatethread.cpp \
    widgets/executor/testsequenceexecutormanage.cpp

# Ресурсы
#RESOURCES += report/reportmanager_resources.qrc
RESOURCES += testsequence_resources.qrc \
    widgets/executor/report/reportmanager_resources.qrc

# Доп. файлы
DISTFILES += \
    report/htmlrep/style.css \
    testsequence.json

FORMS += \
    widgets/settings/testsequencesettingswidget.ui \
    widgets/testsviewer/testsequencetestsviewer.ui \
    widgets/testsviewer/renametestdialog.ui \
#    widgets/executor/testsequenceexecutorwidget.ui \
    widgets/editor/testsequenceeditor.ui \
    widgets/editor/testcaseeditordialog.ui \
    widgets/editor/testsequencesavedialog.ui \
    widgets/executor/testsequenceexecutorwidget.ui \
    widgets/executor/chooseserialnumberdialog.ui
