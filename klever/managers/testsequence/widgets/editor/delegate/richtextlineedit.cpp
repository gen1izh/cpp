#include "richtextlineedit.h"

/*
 * Конструктор элемента RichText текстового поля
 */
RichTextLineEdit::RichTextLineEdit(QWidget *parent)
    : QTextEdit(parent) {
  setLineWrapMode(QTextEdit::NoWrap);
  setWordWrapMode(QTextOption::NoWrap);
  setAcceptRichText(true);
//  setTabChangesFocus(true);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setContextMenuPolicy(Qt::CustomContextMenu);
//  connect( this, SIGNAL( customContextMenuRequested( const QPoint& ) ),
//           this, SLOT( customContextMenuRequested( const QPoint& ) ) );
}

/*
 * Переопределение размера текста
 */
QSize RichTextLineEdit::sizeHint() const {
  QFontMetrics fm(font());
  return QSize(document()->idealWidth() + fm.width("W"),
               fm.height() + 5);
}

/*
 * Возвращает минимальный размер текста
 */
QSize RichTextLineEdit::minimumSizeHint() const {
  QFontMetrics fm( font() );
  return QSize(fm.width("WWWW"), fm.height() + 5);
}

/*
 * Обработчик нажатия на клавишу
 */
void RichTextLineEdit::keyPressEvent(QKeyEvent *event) {
  if ( event->key() == Qt::Key_Enter ||
       event->key() == Qt::Key_Return ) {
    emit returnPressed();
    event->accept();
  }
  else {
    QTextEdit::keyPressEvent( event );
  }
}



