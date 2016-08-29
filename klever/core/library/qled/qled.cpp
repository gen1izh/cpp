/***************************************************************************
 *   Copyright (C) 2010 by P. Sereno                                       *
 *   http://www.sereno-online.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License           *
 *   version 2.1 as published by the Free Software Foundation              *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Lesser General Public License for more details.                   *
 *   http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.               *
 ***************************************************************************/
  
#include <QColor>
#include <QtGlobal>
#include <QtGui>
#include <QPolygon>
#include <QtSvg>
#include <QSvgRenderer>
#include <QRectF>

#include <QDebug>

#include "qled.h"

/*!
  \brief QLed: this is the QLed constructor.
  \param parent: The Parent Widget
*/
QLed::QLed(QWidget *parent)
    : QWidget(parent),
      m_opacity(1.0)
{
   m_value = false;
   m_wink  = false;
   m_onColor  = Red;
   m_offColor = Grey;
   m_shape    = Circle;
   shapes << ":/qled/img/circle_" << ":/qled/img/square_" << ":/qled/img/triang_" << ":/qled/img/round_";
   colors << "red.svg" << "green.svg" << "yellow.svg" << "grey.svg" << "orange.svg" << "purple.svg" << "blue.svg";

   renderer = new QSvgRenderer();
   connect(this, SIGNAL(valueChanged()), this, SLOT(changeRenderColor()));
   connect(this, SIGNAL(colorChanged()), this, SLOT(changeRenderColor()));

   changeRenderColor();
}
QLed::~QLed() {
	delete renderer;
}

/*!
  \brief paintEvent: painting method
  \param QPaintEvent *
  \return void
*/
void QLed::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    if (m_wink){
      painter.setOpacity(m_opacity);
    }

    double boundWidth  = 0.0;
    double boundHeight = 0.0;
    double ratio = renderer->defaultSize().width() /
                   renderer->defaultSize().height();
    if (ratio > 1.0){
      // ширина больше высоты
      boundWidth  = size().width();
      boundHeight = boundWidth * ratio;
    } else if (ratio < 1.0) {
      boundHeight = size().height();
      boundWidth  = boundHeight * ratio;
    } else {
      boundHeight = qMin(size().width(), size().height());
      boundWidth  = boundHeight * ratio;
    }
    QRectF bounds((size().width()  - boundWidth)  / 2,
                  (size().height() - boundHeight) / 2,
                  boundWidth,
                  boundHeight);

    renderer->render(&painter, bounds);
}


/*!
  \brief setOnColor: this method allows to change the On color {Red,Green,Yellow,Grey,Orange,Purple,blue}
  \param ledColor newColor
  \return void
*/
void QLed::setOnColor(ledColor newColor)
{
    if (m_onColor != newColor){
        m_onColor = newColor;
        emit colorChanged();
        update();
    }
}


/*!
  \brief setOffColor: this method allows to change the Off color {Red,Green,Yellow,Grey,Orange,Purple,blue}
  \param ledColor newColor
  \return void
*/
void QLed::setOffColor(ledColor newColor)
{
    if (m_offColor != newColor){
        m_offColor = newColor;
        emit colorChanged();
        update();
    }
}


/*!
  \brief setShape: this method allows to change the led shape {Circle,Square,Triangle,Rounded rectangle}
  \param ledColor newColor
  \return void
*/
void QLed::setShape(ledShape newShape)
{
   m_shape=newShape;
   update();
}


/*!
  \brief setValue: this method allows to set the led value {true,false}
  \param ledColor newColor
  \return void
*/
void QLed::setValue(bool value)
{
   if (m_value != value){
     m_value=value;
     emit valueChanged();
   }
   if (m_value && m_wink){
       QPropertyAnimation *anim = new QPropertyAnimation(this, "opacity", this);
       anim->setDuration(200);
       anim->setStartValue(0.0);
       anim->setEndValue(1.0);
       anim->start(QAbstractAnimation::DeleteWhenStopped);
   }
   update();
}


/*!
  \brief toggleValue: this method toggles the led value
  \param ledColor newColor
  \return void
*/
void QLed::toggleValue()
{ 
	m_value=!m_value;
	update();
  return;
}

void QLed::changeRenderColor()
{
  QString  ledShapeAndColor;

  ledShapeAndColor = shapes[m_shape];

  if(m_value)
      ledShapeAndColor.append(colors[m_onColor]);
  else
      ledShapeAndColor.append(colors[m_offColor]);

  renderer->load(ledShapeAndColor);
}
