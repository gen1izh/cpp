#include "autorizationsettingswidget.h"
#include "autorizationmanager.h"
#include <frameWork/plugins.h>

autorizationSettings::autorizationSettings(QWidget *parent) : QWidget(parent)
{
  // Установка элементов на layout
  QGridLayout *mainLayout = new QGridLayout;

  d = new PersonalData();

  mainLayout->addWidget( d, 0, 0, 1, 2);

  mainLayout->setContentsMargins(1,1,1,1);

  // Установка выравнивания элементов по верхней границе
  mainLayout->setAlignment(Qt::AlignTop);

  // Установка лайаута на форму
  setLayout(mainLayout);

  // Создание коннекторов
  createConnectors();
}

/*
 * Создать коннекторы
 */
void autorizationSettings::createConnectors() {
}


