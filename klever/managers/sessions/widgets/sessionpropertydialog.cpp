#include "sessionpropertydialog.h"

#include "sessionstable.h"

using namespace SessionViewNamespace;

SessionPropertyDialog::SessionPropertyDialog(QDialog *parent) : QDialog(parent)
{
  // Установка флагов для диалогового окна
  setWindowFlags( Qt::Window
                  | Qt::MSWindowsFixedSizeDialogHint
                  | Qt::WindowCloseButtonHint);

  setWindowTitle(tr("Добавление сессии ..."));

  // Инициализация сетки расположения графических компонентов

  addNewSessionGridLayout.setSizeConstraint(QLayout::SetDefaultConstraint);

  //FIXME: Потенциальный баг, надо валидатор делать на поля
  // Создание поля "Название сессии"
  QLabel *nameLabel = new QLabel();
  nameLabel->setText("Название сессии:");
  _nameLineEdit = new QLineEdit;
  _nameLineEdit->setPlaceholderText("Введите название сессии ...");
  _nameLineEdit->setInputMask("XXXXXXXXXXXXXXXXXXXXXX");
  nameLabel->setBuddy(_nameLineEdit);
  addNewSessionGridLayout.addWidget(nameLabel,    0, 0);
  addNewSessionGridLayout.addWidget(_nameLineEdit, 0, 1);

  // Создание поля "Тип изделия"
  QLabel *productTypeLabel = new QLabel();
  productTypeLabel->setText("Тип изделия:");
  _productTypeLineEdit = new QLineEdit;
  _productTypeLineEdit->setInputMask("XXXXXXXXXXXXXXXXXXXXXX");
  _productTypeLineEdit->setPlaceholderText("Введите тип изделия ...");
  productTypeLabel->setBuddy(_productTypeLineEdit);
  addNewSessionGridLayout.addWidget(productTypeLabel,    1, 0);
  addNewSessionGridLayout.addWidget(_productTypeLineEdit, 1, 1);

  // Создание поля "Права доступа"
  QLabel *rightsLabel = new QLabel();
  rightsLabel->setText("Права доступа:");
  _rightsBox = new QComboBox;
  _rightsBox->addItem(Developer);
  _rightsBox->addItem(Operator);
  rightsLabel->setBuddy(_rightsBox);
  addNewSessionGridLayout.addWidget(rightsLabel,    2, 0);
  addNewSessionGridLayout.addWidget(_rightsBox, 2, 1);

  // Создание поля "Серийный номер"
  QLabel *serialNumberLabel = new QLabel();
  serialNumberLabel->setText("Серийный номер:");
  _serialNumberLineEdit = new QLineEdit;
  _serialNumberLineEdit->setPlaceholderText("Введите серийный номер изделия ...");
  _serialNumberLineEdit->setInputMask("999999999999999999999999");
  serialNumberLabel->setBuddy(_serialNumberLineEdit );
  addNewSessionGridLayout.addWidget(serialNumberLabel,    3, 0);
  addNewSessionGridLayout.addWidget(_serialNumberLineEdit, 3, 1);

  // Создание кнопки Accept
  acceptButton.setText("&Принять");
  addNewSessionGridLayout.addWidget(&acceptButton, 4, 0, 1, 3);
  QObject::connect(&acceptButton, SIGNAL(clicked()), this, SLOT(accept()));

  setLayout(&addNewSessionGridLayout);


}

void SessionPropertyDialog::execute()
{
  // Обработка нажатия на кнопку Принять
  if ( exec() == QDialog::Accepted ) {
    if ( _nameLineEdit->text().isEmpty() ) {
      qDebug() << "err: boot: Session name empty!";
      return;
    }

   emit insertNewSession(_nameLineEdit->text(), _productTypeLineEdit->text(),
                         _rightsBox->currentText(), _serialNumberLineEdit->text());


  }
}

