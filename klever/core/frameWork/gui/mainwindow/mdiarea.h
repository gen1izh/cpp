#ifndef MDIAREA_H
#define MDIAREA_H

#include <QWidget>
#include <QMdiArea>
#include <QPixmap>
#include <QPainter>

class MdiArea : public QMdiArea
{

  public:
    MdiArea( QWidget *parent = 0) : QMdiArea(parent){}

  ~MdiArea(){}
  protected:
    void paintEvent(QPaintEvent *event) {
      QMdiArea::paintEvent(event);
      QPixmap pixmap(":/images/mdi_logo.png");
      QPainter painter(viewport());
      int x = (geometry().width()  - pixmap.width())/2;
      int y = (geometry().height() - pixmap.height())/2;
      painter.drawPixmap(x,y,pixmap);
    }
};

#endif // MDIAREA_H
