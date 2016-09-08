#ifndef MODULEINFOMDICHILD_H
#define MODULEINFOMDICHILD_H

#include <QWidget>
#include <QObject>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>

#include <frameWork/base.h>

/*!
 * \brief ModuleInfoMdiChild класс
 */
class ModuleInfoMdiChild : public QWidget {

  Q_OBJECT

  signals:
    void setVisibleSignal(bool visible);

  public:

    ModuleInfoMdiChild();
    ~ModuleInfoMdiChild();

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

};

#endif // MODULEINFOMDICHILD_H
