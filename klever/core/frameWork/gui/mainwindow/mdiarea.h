#ifndef MDIAREA_H
#define MDIAREA_H

#include <QWidget>
#include <QMdiArea>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

#include <QDebug>
#include <QCoreApplication>
#include <frameWork/information.h>

class MdiArea : public QMdiArea
{

  public:
    MdiArea( QWidget *parent = 0) : QMdiArea(parent){}

  ~MdiArea(){}
  protected:
    void paintEvent(QPaintEvent *event) {
      QMdiArea::paintEvent(event); 
      QPixmap pixmap;

      if(Information::instance().logo() != "default") {
          pixmap.load(QCoreApplication::applicationDirPath() + "/" + Information::instance().logo());
      }
      else {
          pixmap.load(QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("mdi_logo.png"));
      }

      QImage image(pixmap.size(), QImage::Format_ARGB32_Premultiplied);
      image.fill(Qt::darkGray);
      QPainter p(&image);
      p.setOpacity(0.0);
      p.drawPixmap(0, 0, pixmap);
      p.end();
      QPixmap output = QPixmap::fromImage(image);
      output.setMask(pixmap.mask());

      QPainter painter(viewport());
      int x = (geometry().width()  - output.width())/2;
      int y = (geometry().height() - output.height())/2;
      painter.drawPixmap(x, y, output);
    }
};

#endif // MDIAREA_H
