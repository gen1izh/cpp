#include "richtextdelegate.h"

/*
 * Конструктор для делегата RichText
 */
RichTextDelegate::RichTextDelegate(QObject *parent)
    : QItemDelegate(parent) {
  checkbox = new QCheckBox;
  // Устанавливаем ширину флажка чуть больше высоты.
  // Это необходимо, чтобы сделать побольше места между меткой и флажком.
  checkbox->setFixedSize( qRound(1.3 * checkbox->sizeHint().height()),
                          checkbox->sizeHint().height() );
  label = new QLabel;
  label->setTextFormat( Qt::RichText );
  label->setWordWrap( false );
}

/*
 * Рисует элемент с модельным индексом.
 * Редко переопределяется для простых данных - текста, дат, чисел.
 */
void RichTextDelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const {

  // Создаем палитру
  bool selected = option.state & QStyle::State_Selected;
  QPalette palette( option.palette );
  palette.setColor( QPalette::Active, QPalette::Window,
                    selected ? option.palette.highlight().color()
                            : option.palette.base().color() );
  palette.setColor( QPalette::Active, QPalette::WindowText,
                    selected
                    ? option.palette.highlightedText().color()
                    : option.palette.text().color() );

  // Настраивается флажок
  int yOffset = checkbox->height() < option.rect.height()
                  ? (option.rect.height() - checkbox->height()) / 2 : 0;
  QRect checkboxRect( option.rect.x(), option.rect.y() + yOffset,
                      checkbox->width(), checkbox->height() );
  checkbox->setPalette( palette );
  bool checked = index.model()->data( index, Qt::CheckStateRole )
                                     .toInt() == Qt::Checked;
  checkbox->setChecked( checked );

  // Настраивается метка
  QRect labelRect(  option.rect.x() + checkbox->width(),
                    option.rect.y(), option.rect.width() - checkbox->width(),
                    option.rect.height() );
  label->setPalette(palette);
  label->setFixedSize(qMax(0, labelRect.width()),
                      labelRect.height());
  QString html = index.model()->data(index, Qt::DisplayRole)
                                     .toString();
  label->setText( html );

  // Рисование виджетов
  QString checkboxKey = QString( "CHECKBOX:%1.%2" ).arg( selected )
                                                   .arg( checked );
  paintWidget( painter, checkboxRect, checkboxKey, checkbox );
  QString labelKey = QString("LABEL:%1.%2.%3x%4").arg(selected)
          .arg(html).arg(labelRect.width()).arg(labelRect.height());
  paintWidget(painter, labelRect, labelKey, label);
}

/*
 * Рисование виджетов
 */
void RichTextDelegate::paintWidget(QPainter *painter,
        const QRect &rect, const QString &cacheKey,
        QWidget *widget) const {
  QPixmap pixmap(widget->size());
  if ( !QPixmapCache::find( cacheKey, &pixmap ) ) {
    widget->render(&pixmap);
    QPixmapCache::insert(cacheKey, pixmap);
  }
  painter->drawPixmap(rect, pixmap);
}

/*
 * Переопределение длины текста без html тегов
 */
QSize RichTextDelegate::sizeHint( const QStyleOptionViewItem &option,
                                  const QModelIndex &index ) const {
  QString html = index.model()->data( index, Qt::DisplayRole)
                                     .toString();
  document.setDefaultFont( option.font );
  document.setHtml( html );
  return QSize( document.idealWidth(), option.fontMetrics.height() );
}

/*
 * Создание редактора для элемента с переданным модельным индексом
 */
QWidget *RichTextDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option, const QModelIndex&) const {
  RichTextLineEdit *editor = new RichTextLineEdit(parent);
  editor->viewport()->setFixedHeight(option.rect.height());
  QObject::connect(editor, SIGNAL(returnPressed()),
          this, SLOT(closeAndCommitEditor()));

  QObject::connect(editor, SIGNAL(textChanged()),
          this, SLOT(textChangedEditor()));


  return editor;
}

/*
 * Установка данных для модели
 */
void RichTextDelegate::setEditorData(QWidget *editor,
        const QModelIndex &index) const {
  QString html = index.model()->data( index, Qt::DisplayRole )
                                     .toString();
  RichTextLineEdit *lineEdit = qobject_cast<RichTextLineEdit*>(
                                            editor);
  Q_ASSERT( lineEdit );
  lineEdit->setHtml( html );
}

/*
 * Установка данных в модель после завершения операции редактирования
 */
void RichTextDelegate::setModelData( QWidget *editor,
        QAbstractItemModel *model, const QModelIndex &index) const {
  RichTextLineEdit *lineEdit = qobject_cast<RichTextLineEdit*>( editor );
  Q_ASSERT( lineEdit );
  model->setData( index, ( ( QTextEdit* )lineEdit )->toPlainText() );
}

/*
 * Генерация сигнала успешного завершения редактора
 */
void RichTextDelegate::closeAndCommitEditor() {
  RichTextLineEdit *lineEdit = qobject_cast<RichTextLineEdit*>(
                                            sender() );
  Q_ASSERT( lineEdit );
  emit commitData(lineEdit);
  emit closeEditor(lineEdit);

}

/*
 *
 */
void RichTextDelegate::textChangedEditor() {
  emit changedData();
}

