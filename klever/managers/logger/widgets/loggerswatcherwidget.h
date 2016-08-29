#ifndef LOGGERSWATCHERWIDGET_H
#define LOGGERSWATCHERWIDGET_H

#include <QWidget>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>

#include "loggerstabswidgets.h"

class LoggersWatcherWidget : public QWidget
{
  Q_OBJECT
  QPushButton *_prevButton;
  QPushButton *_nextButton;
  QLineEdit   *_pageNumberEdit;
  QLabel      *_pagesCountLabel;

  LoggersTabsWidgets *_ltw;

public:
  explicit LoggersWatcherWidget(QWidget *parent = 0, LoggersTabsWidgets *lo=NULL);

public slots:
  void prevButtonHandler();
  void nextButtonHandler();
  void setPageCountsAndCurrentPage(int i, int count);
};

#endif // LOGGERSWATCHERWIDGET_H
