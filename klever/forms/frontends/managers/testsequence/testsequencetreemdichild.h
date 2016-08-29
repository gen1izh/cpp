#ifndef TESTSEQUENCEMDICHILD_H
#define TESTSEQUENCEMDICHILD_H

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

class TestSequenceMdiChild : public QWidget {

  Q_OBJECT

  public:
    TestSequenceMdiChild();
    ~TestSequenceMdiChild();

    void closeEvent( QCloseEvent *event );

  signals:
    void setVisibleSignal(bool visible);

};

#endif // TESTSEQUENCEMDICHILD_H
