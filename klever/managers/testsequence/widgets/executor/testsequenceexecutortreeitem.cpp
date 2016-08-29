#include "testsequenceexecutortreeitem.h"

TestsequenceExecutorTreeItem::TestsequenceExecutorTreeItem(const QString &name,
                                                             const QString &avarage,
                                                             const bool debugBreak,
                                                             TestsequenceExecutorTreeItem *parent)
        : _debugBreak(debugBreak), _name(name), _avarage_time(avarage),
          _parent(parent) {
  if (_parent) {
    _parent->addChild(this);
  }
}

/*
 * Изымает элемент тест-кейса из тестовой последовательности
 */
TestsequenceExecutorTreeItem* TestsequenceExecutorTreeItem::takeChild(int row) {
  TestsequenceExecutorTreeItem *item = _children.takeAt(row);
  Q_ASSERT( item );
  item->_parent = 0;
  return item;
}


