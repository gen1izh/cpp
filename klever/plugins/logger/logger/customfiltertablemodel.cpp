#include "customfiltertablemodel.h"

/**************************************************************************
 *              Реализация модели данных фильтра по источнику
 **************************************************************************/

/*
 *  Конструктор модели данных фильтра по источнику
 */
CustomFilterTableModel::CustomFilterTableModel(QObject *parent) :
    QAbstractTableModel(parent) {
  _mRowCount = 0;
  filter     = NULL;
}

/*
 * Установка количества строк
 */
void CustomFilterTableModel::setRowCount( int count ) {
  if ( _mRowCount != 0 ) {
    beginRemoveRows( QModelIndex(), 0, _mRowCount - 1 );
    removeRows( 0, _mRowCount );
    endRemoveRows();
  }

  _mRowCount = count;

  if ( _mRowCount != 0 ) {
    beginInsertRows( QModelIndex(), 0, _mRowCount - 1 );
    insertRows( 0, _mRowCount );
    endInsertRows();
  }

  emit layoutChanged();
}

/*
 * Прорисовка данных в таблице
 */
QVariant CustomFilterTableModel::data( const QModelIndex &index, int role ) const {
  if ( !index.isValid() ) {
    return QVariant();
  }

  if ( role == Qt::TextAlignmentRole ) {
    return Qt::AlignHCenter;
  }

  if ( role != Qt::DisplayRole ) {
    return QVariant();
  }

  if ( !filter ) {
    return QVariant();
  }

  if ( index.row() >= filter->count() ) {
    return QVariant();
  }

  if ( index.column() == 0 ) {
    return filter->keys().at( index.row() );
  }

  if ( index.column() == 1 ) {
    return filter->values().at( index.row() );
  }

  return QVariant();
}

/*
 * Запись данных в модель
 */
bool CustomFilterTableModel::setData( const QModelIndex &index,
                                   const QVariant &value,
                                   int role ) {
  if ( !index.isValid() ) {
    return false;
  }

  if ( role != Qt::EditRole ) {
    return false;
  }

  if ( index.column() != 1 ) {
    return false;
  }

  if ( !filter ) {
    return false;
  }

  if ( index.row() >= filter->count() ) {
    return false;
  }

  bool ok;
  QString key = filter->keys().at( index.row() );
  filter->remove( key );
  filter->insert( key, (bool)value.toInt(&ok) );

  return true;
}

/*
 * Выделить все пункты
 */
void CustomFilterTableModel::selectAll() {
  for ( int i = 0; i < filter->count(); i++ ) {
    QString key = filter->keys().at(i);
    filter->remove( key );
    filter->insert( key, true );
  }
  emit layoutChanged();
}

/*
 * Снять галочки со всех пунктов
 */
void CustomFilterTableModel::deselectAll() {
  for ( int i = 0; i < filter->count(); i++ ) {
    QString key = filter->keys().at(i);
    filter->remove( key );
    filter->insert( key, false );
  }
  emit layoutChanged();
}

/*
 * Строка заголовка таблицы источников сообщений окна фильтрации по источнику
 */
QVariant CustomFilterTableModel::headerData( int section,
                                          Qt::Orientation orientation,
                                          int role ) const {
  if ( role != Qt::DisplayRole ) {
    return QVariant();
  }

  if ( orientation == Qt::Horizontal ) {
    QString sectionNames[2] = { tr( "Источник" ), tr( "Отображать" ) };
    if ( ( section >= 0 )&&( section < 2 ) ) {
      return sectionNames[ section ];
    }
  };

  return QVariant();
}

/*
 * Возвращает количество колонок
 */
int CustomFilterTableModel::columnCount( const QModelIndex &parent ) const {
  Q_UNUSED(parent);
  return 2;
}

/*
 * Возвращает количество строк
 */
int CustomFilterTableModel::rowCount(const QModelIndex &parent) const {
  if ( parent.isValid() ) {
    return 0;
  }
  else {
    if ( filter ) {
      return filter->count();
    }
    else {
      return 0;
    }
  }
}

/*
 * Returns the item flags for the given index.
 * The base class implementation returns a combination
 * of flags that enables the item (ItemIsEnabled)
 * and   allows it to be selected (ItemIsSelectable).
 */
Qt::ItemFlags CustomFilterTableModel::flags( const QModelIndex &index ) const {
  Qt::ItemFlags flags = QAbstractTableModel::flags( index );
  flags |= Qt::ItemIsEditable;
  return index.isValid() ? ( flags | Qt::ItemIsSelectable) : flags;
}

/*
 * Переустановка количества строк в таблице.
 */
void CustomFilterTableModel::update() {
  if ( filter ) {
    setRowCount( filter->count() );
  }
}

