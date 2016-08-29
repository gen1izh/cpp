#include "testsequenceeditortreeitem.h"


/******************************************************************************
 *                  Класс работы с элементов дерева проверок
 ******************************************************************************/

/*
 * Конструктор элемента дерева тестовой последовательности
 */
TestSequencesEditorTreeItem::TestSequencesEditorTreeItem(const QString &name,
                                              const QString &exectable,
                                              const QString &avarage,
                                              const QString &desc,
                                              const QString &path,
                                              const bool debugBreak,
                                              TestSequencesEditorTreeItem *parent )
        : _debugBreak(debugBreak), _name(name), _exectable_flag(exectable), _avarage_time(avarage),
          _desc(desc), _path(path), _parent(parent) {
  if (_parent) {
    _parent->addChild( this );
  }
}

/*
 * Изымает элемент тест-кейса из тестовой последовательности
 */
TestSequencesEditorTreeItem* TestSequencesEditorTreeItem::takeChild( int row ) {
  TestSequencesEditorTreeItem *item = _children.takeAt( row );
  Q_ASSERT( item );
  item->_parent = 0;
  return item;
}


