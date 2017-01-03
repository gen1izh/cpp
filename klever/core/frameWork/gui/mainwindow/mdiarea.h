#ifndef MDIAREA_H
#define MDIAREA_H

#include <QWidget>
#include <QMdiArea>
#include <QPixmap>
#include <QPainter>

#include <QDebug>
#include <QCoreApplication>

class MdiArea : public QMdiArea
{

  public:
    MdiArea( QWidget *parent = 0) : QMdiArea(parent){}

  ~MdiArea(){}
  protected:
    void paintEvent(QPaintEvent *event) {
      QMdiArea::paintEvent(event);
      // QPixmap pixmap(":/images/mdi_logo.png");
      QPixmap pixmap;

      QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("mdi_logo.png");
      pixmap.load(path);


      QPainter painter(viewport());
      int x = (geometry().width()  - pixmap.width())/2;
      int y = (geometry().height() - pixmap.height())/2;
      painter.drawPixmap(x,y,pixmap);
    }
};

#endif // MDIAREA_H
