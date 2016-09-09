#include "modulesmainwindget.h"
#include <frameWork/managers.h>
#include <library/setupApi/app.h>

ModulesMainWindget::ModulesMainWindget(QWidget *parent) : QWidget(parent) {
  infoAndChangeLogTab = new QToolBox();

  // Необходимые и достаточные требования работоспособности модуля
  informationTextEdit = new QTextEdit();

  // Лист изменений в модуле
  changeLogTextEdit = new QTextEdit();

  // Инициализация сетки расположения графических компонентов
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  _modulesInformationList = new QListWidget();

  moreButton  = new QPushButton();
  moreButton->setText("Подробнее о модуле");

  grid->addWidget(_modulesInformationList,  0, 0, 1, 2);
  grid->addWidget(moreButton,  1, 0, 1,2);

  /* Добавление сетки на слой виджета */
  setLayout(grid);

  setWindowTitle("Информация о модуле");

  /* Инициализация сетки расположения графических компонентов */
  QGridLayout *dialogGrid = new QGridLayout();
  dialogGrid->setSizeConstraint(QLayout::SetDefaultConstraint);


  infoAndChangeLogTab->addItem(informationTextEdit, QString("Информация"));
  infoAndChangeLogTab->addItem(changeLogTextEdit,   QString("Лист изменения"));

  dialogGrid->addWidget( infoAndChangeLogTab, 2, 0, 1, 2 );

  dlg.setWindowTitle( tr(" Подробнее о модуле... ") );

  // Добавление сетки на слой виджета
  dlg.setLayout( dialogGrid );

  dlg.setFixedSize(400,300);

  QObject::connect(moreButton, SIGNAL(clicked()),
                   this, SLOT(openDialog()));

  setWindowIcon(QIcon(":/images/modules_info.png"));

}

/*
 * Установка списка названий модулей
 */
void ModulesMainWindget::setModulesInformationList(QStringList lst) {
  QFont fnt;
//  fnt.setForeground(Qt::red);
  fnt.setStyle(QFont::StyleItalic);
  _modulesInformationList->setFont(fnt);
  _modulesInformationList->addItems(lst);
}

/*
 * Открытие диалогового окна с подробным описанием каждого модуля
 */
void ModulesMainWindget::openDialog() {
  QString txt;
  if (_modulesInformationList->currentRow()>=0) {
    txt = _modulesInformationList->currentItem()->text();
  }
  else {
    txt.clear();
  }

  emit openModulesInformationDialog(txt,
                                    _modulesInformationList->currentRow());

}



/*
 * Установка списка названий модулей
 */
void ModulesMainWindget::setInfoAndChangeLog(QString info, QString changelog) {
  informationTextEdit->clear();
  changeLogTextEdit->clear();

  informationTextEdit->setPlainText(info);
  changeLogTextEdit->setPlainText(changelog);

  if ( dlg.exec() == QDialog::Accepted ) {
  }
}



