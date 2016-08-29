#include "optimesettingswidget.h"
#include "../../optimemanager.h"
#include <frameWork/cveManager.h>

OptimeSettings::OptimeSettings(QWidget *parent) : QWidget(parent)
{
  // Установка элементов на layout
  QGridLayout *mainLayout = new QGridLayout;

  // mainLayout->addWidget( Указатель_на_элемент, 0, 0, 1, 2);

  mainLayout->setContentsMargins(1,1,1,1);

  // Установка выравнивания элементов по верхней границе
  mainLayout->setAlignment(Qt::AlignTop);

  _clearCveOperationTimeButton = new QPushButton();
  _clearProductOperationTimeButton = new QPushButton();

  _clearCveOperationTimeButton->setText(tr("Очистить наработку КПА"));
  _clearProductOperationTimeButton->setText(tr("Очистить наработку изделия"));

  _cveOperationTimeEdit = new QLineEdit();
  _productOperationTimeEdit = new QLineEdit();

  _cveOperationTimeLabel = new QLabel();
  _productOperationTimeLabel = new QLabel();

  _cveOperationTimeLabel->setText(tr("Наработку КПА:"));
  _productOperationTimeLabel->setText(tr("Наработку изделия:"));

  mainLayout->addWidget(_cveOperationTimeLabel, 0, 0);
  mainLayout->addWidget(_productOperationTimeLabel, 1, 0);
  mainLayout->addWidget(_cveOperationTimeEdit, 0, 1);
  mainLayout->addWidget(_productOperationTimeEdit, 1, 1);
  mainLayout->addWidget(_clearCveOperationTimeButton, 0, 2);
  mainLayout->addWidget(_clearProductOperationTimeButton, 1, 2);

  // Установка лайаута на форму
  setLayout(mainLayout);

  // Создание коннекторов
  createConnectors();

}

OptimeSettings::~OptimeSettings()
{
}

/*
 * Создать коннекторы
 */
void OptimeSettings::createConnectors() {
  connect(_clearCveOperationTimeButton, SIGNAL(clicked(bool)), this, SLOT(clearCveOperationTime()));
  connect(_clearProductOperationTimeButton, SIGNAL(clicked(bool)), this, SLOT(clearProductOperationTime()));
}

/*
 * Очистка, обнуление времени наработки для КПА
 */
void OptimeSettings::clearCveOperationTime() {
  QSettings settings("Irz", "OptimeManager");
  settings.beginGroup("operation_time");
  settings.setValue("cve", 0);
  settings.endGroup();
  emit clearCveOperationTimeSignal();
}

/*
 * Очистка, обнуление времени наработки для изделия
 */
void OptimeSettings::clearProductOperationTime() {
  QSettings settings("Irz", "OptimeManager");
  settings.beginGroup("operation_time");
  settings.setValue(QString("product_%1").arg(Cve::instance().getParameterValue(QString("/serialNumber"),
                                                                                QString("000000"))),
                                                                                0);
  settings.endGroup();
  emit clearProductOperationTimeSignal();
}
