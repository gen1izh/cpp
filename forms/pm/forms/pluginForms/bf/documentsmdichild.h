#ifndef DOCUMENTSMDICHILD_H
#define DOCUMENTSMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include <plugins/logger/logger.h>

class DocumentsMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:
    void closeEvent(QCloseEvent *event);

    DocumentsMdiChild();
    ~DocumentsMdiChild();

};

#endif // DOCUMENTSMDICHILD_H
