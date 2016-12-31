#include "customfilteritemdelegate.h"

/**************************************************************************
 *              Реализация делегата фильтра по источнику
 **************************************************************************/

/*
 * Инициализация фильтра
 */
CustomFilterItemDelegate::CustomFilterItemDelegate(QObject *parent)
    : QItemDelegate(parent) {}

/*
 * Прямоугольники checkBox`ов
 */
const QRect CustomFilterItemDelegate::CheckBoxRect(
  const QStyleOptionViewItem &viewItemStyleOptions ) const {
  QStyleOptionButton check_box_style_option;
  QRect checkBoxRect = QApplication::style()->subElementRect(
                         QStyle::SE_CheckBoxIndicator,
                         &check_box_style_option );
  QPoint checkBoxPoint( viewItemStyleOptions.rect.x() +
                          viewItemStyleOptions.rect.width() / 2 -
                          checkBoxRect.width() / 2,
                          viewItemStyleOptions.rect.y() +
                          viewItemStyleOptions.rect.height() / 2 -
                          checkBoxRect.height() / 2);
  return QRect( checkBoxPoint, checkBoxRect.size() );
}

/*
 * Создание редактора
 */
QWidget *CustomFilterItemDelegate::createEditor(
          QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const {

  Q_UNUSED(parent);
  Q_UNUSED(option);
  Q_UNUSED(index);
  return NULL;
}

/*
 * Прорисовка источников фильтрации
 */
void CustomFilterItemDelegate::paint(
                                      QPainter *painter,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index) const {

  if ( index.column() == 1 ) {
    bool checked = index.model()->data( index, Qt::DisplayRole ).toBool();
    QStyleOptionButton checkBoxStyleOption;
    checkBoxStyleOption.state |= QStyle::State_Enabled;
    if ( checked ) {
      checkBoxStyleOption.state |= QStyle::State_On;
    }
    else {
      checkBoxStyleOption.state |= QStyle::State_Off;
    }
    checkBoxStyleOption.rect = CheckBoxRect( option );
    QApplication::style()->drawControl( QStyle::CE_CheckBox,
                                        &checkBoxStyleOption,
                                        painter );
  }
  else {
    QItemDelegate::paint( painter, option, index );
  }
}

/*
 * Событие редактирования данных
 */
bool CustomFilterItemDelegate::editorEvent(
                                QEvent *event,
                                QAbstractItemModel *model,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index ) {

    if ( index.column() == 1 ) {
      if ( (event->type() == QEvent::MouseButtonRelease ) ||
           (event->type() == QEvent::MouseButtonDblClick ) ) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>( event );

        if ( mouse_event->button() != Qt::LeftButton ||
            !CheckBoxRect( option ).contains( mouse_event->pos() ) ) {
          return false;
        }

        if ( event->type() == QEvent::MouseButtonDblClick ) {
          return true;
        }
      }
      else if ( event->type() == QEvent::KeyPress ) {
        if ( static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
             static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select ) {
          return false;
        }
      }
      else {
        return false;
      }
      bool checked = index.model()->data( index, Qt::DisplayRole ).toBool();
      return model->setData( index, !checked, Qt::EditRole );
    }

  QItemDelegate::editorEvent( event, model, option, index );

  return true;
}

/*
 * Установка данных редактора
 */
void CustomFilterItemDelegate::setEditorData(
  QWidget *editor,
  const QModelIndex &index) const {

  Q_UNUSED(editor);
  Q_UNUSED(index);
}

/*
 * Установка модели данных
 */
void CustomFilterItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const {
  Q_UNUSED(editor);
  Q_UNUSED(index);
  Q_UNUSED(model);
}

/*
 * Обновить редактор
 */
void CustomFilterItemDelegate::updateEditorGeometry(
          QWidget *editor,
    const QStyleOptionViewItem &option,
    const QModelIndex &/* index */) const {
  editor->setGeometry( option.rect );
}

