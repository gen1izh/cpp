#ifndef TEXTEDITORMDICHILD_H
#define TEXTEDITORMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>
#include <plugins/logger/logger.h>

class TextEditorMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:
    void closeEvent(QCloseEvent *event);

    TextEditorMdiChild();
    ~TextEditorMdiChild();

};

#endif // TEXTEDITORMDICHILD_H
