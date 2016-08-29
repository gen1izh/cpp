#include "qlampwidget.h"

/*
 *  Инициализация виджета
 */
QLampWidget::QLampWidget( QWidget *parent ) : QFrame(parent) {
  _iconLabel = new QLabel;
  _iconLabel->setEnabled( true );
  _iconLabel->setMinimumSize(16, 16 );
  _iconLabel->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed);

  _txtLabel = new QLabel;
  _txtLabel->setAlignment( Qt::AlignLeft );

  QGridLayout *layout = new QGridLayout();
  setLayout(layout);
  layout->addWidget( _iconLabel, 0, 0 );
  layout->addWidget( _txtLabel, 0, 1 );

  layout->setContentsMargins(0, 0, 0, 0);
  setDisableLamp();
}

/*
 * Перегруженный конструктор QLampWidget
 */
QLampWidget::QLampWidget (QString label, int colorIndex, int rowIndex, QWidget *parent) : QFrame(parent)
{

  _iconLabel = new QLabel;
  _iconLabel->setEnabled( true );
  _iconLabel->setMinimumSize(16, 16 );
  _iconLabel->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed);

  _txtLabel = new QLabel(label);
  _txtLabel->setAlignment( Qt::AlignLeft );

  QGridLayout *layout = new QGridLayout();
  setLayout(layout);
  if (rowIndex % 2) {
    layout->addWidget( _iconLabel, rowIndex / 2, 0 );
    layout->addWidget( _txtLabel, rowIndex / 2, 1 );
  }
  else {
    layout->addWidget( _iconLabel, rowIndex / 2, 2 );
    layout->addWidget( _txtLabel, rowIndex / 2, 3 );
  }

  switch (colorIndex) {
    case IS_LAMP_ON:
      setOnLamp();
      break;
    case IS_LAMP_OFF:
      setOffLamp();
      break;
    case IS_LAMP_DISABLE:
      setDisableLamp();
      break;
    case IS_LAMP_FAIL:
      setFailLamp();
      break;
    case IS_LAMP_PING:
      setPingLamp();
      break;
    case IS_LAMP_TRAFFIC:
      setTrafficLamp();
      break;
    case IS_LAMP_READY:
      setReadyLamp();
      break;
    default:
      setDisableLamp();
      break;
  }
}

/*
 * Включение светодиода
 */
void QLampWidget::setOnLamp() {
  QIcon icon(":/lamplib/img/active.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_ON;
}

/*
 * Ожидание готовности
 */
void QLampWidget::setReadyLamp() {
  QIcon icon(":/lamplib/img/ready.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_READY;
}

/*
 * Отключение светодиода
 */
void QLampWidget::setOffLamp() {
  QIcon icon(":/lamplib/img/no_active.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_OFF;
}

/*
 * Сигнализация недоступности светодиода
 */
void QLampWidget::setDisableLamp() {
  QIcon icon(":/lamplib/img/disable.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_DISABLE;
}

/*
 * Сигнализация ошибки
 */
void QLampWidget::setFailLamp() {
  QIcon icon(":/lamplib/img/fail.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_FAIL;
}

/*
 * Сигнализация процесса
 */
void QLampWidget::setPingLamp() {
  QIcon icon(":/lamplib/img/ping.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_PING;
}

/*
 * Сигнализация трафика
 */
void QLampWidget::setTrafficLamp() {
  QIcon icon(":/lamplib/img/traffic.png");
  QPixmap pixmap = icon.pixmap(QSize(16,16), QIcon::Normal, QIcon::On);
  _iconLabel->setPixmap(pixmap);

  _state = IS_LAMP_TRAFFIC;
}

