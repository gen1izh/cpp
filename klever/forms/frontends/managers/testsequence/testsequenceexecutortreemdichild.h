#ifndef TESTSEQUENCE_EXECUTOR_TREE_MDI_CHILD_H
#define TESTSEQUENCE_EXECUTOR_TREE_MDI_CHILD_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCloseEvent>
#include <QDebug>
#include <QToolBar>
#include <QAction>
#include <QMenu>

#include <frameWork/cve.h>

#include <library/message/messagelibrary.h>

class TestsequenceExecutorMdiChild : public QWidget {

  Q_OBJECT

  public:
    TestsequenceExecutorMdiChild();
    ~TestsequenceExecutorMdiChild();

    void closeEvent( QCloseEvent *event );

  signals:
    void setVisibleSignal(bool visible);

};

#endif // TESTSEQUENCE_EXECUTOR_TREE_MDI_CHILD_H
