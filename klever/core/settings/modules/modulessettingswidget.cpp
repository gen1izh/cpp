#include "modulessettingswidget.h"
#include <frameWork/managers.h>

using namespace Core;

/*
 * Установка соединений
 */
void ModulesSettingsWidget::createConnections() {

  // Подключение двойного нажатия на модуль в списке модулей
  connect(_modulesList, SIGNAL(doubleClicked(const QModelIndex &)),
          this, SLOT(moduleCountChanged(const QModelIndex &)));

}

/*
 * Конструктор виджета настроек
 */
ModulesSettingsWidget::ModulesSettingsWidget(QWidget *parent) : QWidget(parent) {

  AppSetupApi  appsetup;

  // Инициализация сетки расположения графических компонентов
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint(QLayout::SetDefaultConstraint);

  _modulesWidgetsNamesLabel = new QLabel(tr("Названия виджетов:"));
  _modulesWidgetsNamesBox   = new QComboBox();
  _modulesListLabel         = new QLabel(tr("Список модулей:"));

  _modulesList      = new QListView();
  _modulesListModel = new ModulesListModel();
  _modulesList->setModel(_modulesListModel);

  grid->setContentsMargins(1,1,1,1);

  createConnections();

  if (Managers::instance().boot()->hasRightUser(DEBUG_MODE)) {
    grid->addWidget(_modulesWidgetsNamesLabel, 0, 0);
    grid->addWidget(_modulesWidgetsNamesBox, 0, 1);

    grid->addWidget(_modulesListLabel, 1, 0);
    grid->addWidget(_modulesList,      2, 0, 1, 2);
  }
  else {
    grid->addWidget(_modulesListLabel, 1, 0);
    grid->addWidget(_modulesList,      2, 0, 1, 2);
  }

  /* Добавление сетки на слой виджета */
  setLayout( grid );

}

/*
 * Функция установки списка имен виджетов
 */
void ModulesSettingsWidget::setWidgetsNamesItems(QStringList lst) {
  if (Managers::instance().boot()->hasRightUser(DEBUG_MODE)) {
    _modulesWidgetsNamesBox->addItems(lst);
  }
}

/*
 * Изменение количества устройств на модуле
 */
void ModulesSettingsWidget::moduleCountChanged(const QModelIndex &index) {
  AppSetupApi  appsetup;

  QDialog dlg;

  // Установка флагов для диалогового окна
  dlg.setWindowFlags(   Qt::Window
                      | Qt::MSWindowsFixedSizeDialogHint
                      | Qt::WindowCloseButtonHint);

  dlg.setWindowTitle( tr(" Задание параметров модуля при инициализации ... ") );

  // Инициализация сетки расположения графических компонентов
  QGridLayout modulesCounterGridLayout;
  modulesCounterGridLayout.setSizeConstraint(QLayout::SetDefaultConstraint);

  // Создание поля "Количество устройств"
  QLabel *countLabel = new QLabel();
  countLabel->setText("Количество устройств:");
  QLineEdit *countLineEdit = new QLineEdit;
  countLineEdit->setPlaceholderText("Введите количество устройств ...");

  countLineEdit->setText(
        appsetup.getApplicationParam(QString("Main"),
                                     QString("/moduleCount%1").arg(index.row())));

  countLineEdit->setInputMask("NN");
  countLabel->setBuddy(countLineEdit);
  modulesCounterGridLayout.addWidget(countLabel,    0, 0);
  modulesCounterGridLayout.addWidget(countLineEdit, 0, 1);

  // Создание кнопки Accept
  QPushButton acceptButton("&Принять");

  modulesCounterGridLayout.addWidget(&acceptButton, 1, 0, 1, 3);

  QObject::connect(&acceptButton, SIGNAL(clicked()),
                   &dlg, SLOT(accept()));

  dlg.setLayout( &modulesCounterGridLayout );

  // Обработка нажатия на кнопку Принять
  if ( dlg.exec() == QDialog::Accepted ) {
    appsetup.setApplicationParam(QString("Main"),
                                 QString("/moduleCount%1").arg(index.row()),
                                 countLineEdit->text());
  }

}
