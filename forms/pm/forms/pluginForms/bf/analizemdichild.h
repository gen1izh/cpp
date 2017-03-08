#ifndef ANALYSISMDICHILD_H
#define ANALYSISMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include <plugins/logger/logger.h>

class AnalysisMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:
    void closeEvent(QCloseEvent *event);

    AnalysisMdiChild();
    ~AnalysisMdiChild();

};

#endif // ANALYSISMDICHILD_H
