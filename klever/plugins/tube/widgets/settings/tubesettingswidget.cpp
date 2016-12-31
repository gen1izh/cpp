#include "tubesettingswidget.h"
#include "../../tubemanager.h"
#include <frameWork/managers.h>

TubeSettings::TubeSettings(QWidget *parent) : QWidget(parent)
{
  // Установка элементов на layout
  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->setContentsMargins(1,1,1,1);

  // Установка выравнивания элементов по верхней границе
  mainLayout->setAlignment(Qt::AlignTop);

  _table = new QTableWidget(200, 2, this);
  _timer = new QTimer();
  _timer->setInterval(1000);
  _timer->start();

  QStringList lst;

  lst << "Ключ" << "Значение";

  _table->setHorizontalHeaderLabels(lst);
  _table->setColumnWidth(0, 100);
  _table->setColumnWidth(1, 100);

  QTableWidgetItem *item;

  for (int i = 0; i < 200; i++)
    for (int j = 0; j < 2; j++) {
      item = new QTableWidgetItem("");
      _table->setItem(i, j, item);
    }

  _table->setSelectionBehavior(QAbstractItemView::SelectRows);

  QHashIterator<QString, Parameter *> _parameters = Core::Base::instance().params();
  QHashIterator<QString, Parameter *> i(_parameters);

  int k = 0;

  while (i.hasNext()) {
    i.next();
    _table->item(k, 0)->setText(i.key());
    _table->item(k, 1)->setText(i.value()->getValue().toString());
    k++;
  }

  mainLayout->addWidget(_table);

  // Установка лайаута на форму
  setLayout(mainLayout);

  // Создание коннекторов
  createConnectors();

}

/*
 * Создать коннекторы
 */
void TubeSettings::createConnectors() {
  connect(_timer, SIGNAL(timeout()), this, SLOT(updateTable()));
}

/*
 * Обновление таблицы ключей трубы
 */
void TubeSettings::updateTable() {
  QHashIterator<QString, Parameter *> _parameters = Core::Base::instance().params();
  QHashIterator<QString, Parameter *> i(_parameters);

  int k = 0;
  // _table->clear();

  while (i.hasNext()) {
    i.next();
    _table->item(k, 0)->setText(i.key());
    _table->item(k, 1)->setText(i.value()->getValue().toString());
    k++;
  }

}


