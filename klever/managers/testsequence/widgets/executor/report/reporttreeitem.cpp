#include "reporttreeitem.h"

/*
 * Вставляет элемент в список дочерних
 */
void ReportTreeItem::insertChild(int row, ReportTreeItem *item)
{
  item->_parent = this;
  _children.insert(row, item);
}

/*
 * Добавление дочернего элемента
 */
void ReportTreeItem::addChild(ReportTreeItem *item) {
  item->_parent = this;
  _children << item;
}


/*
 * Изымает элемент из отчета
 */
ReportTreeItem *ReportTreeItem::takeChild(int row) {
  ReportTreeItem *item = _children.takeAt( row );
  Q_ASSERT( item );
  item->_parent = 0;
  return item;
}
