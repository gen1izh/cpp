#include "settingswidget.h"

#include <QGridLayout>

planSettings::planSettings(QWidget *parent) : QWidget(parent)
{
    // Установка элементов на layout
    QGridLayout *mainLayout = new QGridLayout;

    // mainLayout->addWidget( Указатель_на_элемент, 0, 0, 1, 2);

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
void planSettings::createConnectors() {
}

