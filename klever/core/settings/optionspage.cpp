#include "optionspage.h"

/* Глобальные данные */
#include <frameWork/cve.h>
#include <managers/logger/cveLogger.h>
/* Менеджер сессии */
//#include <managers/sessions/sessionmanager.h>

#include <frameWork/cveManager.h>

#include <library/setupApi/app.h>

OptionsPage::OptionsPage(QWidget *parent)
    : QWidget(parent) {

  AppSetupApi appsetup;
  bool        ok;

  _textLabel  = new QLabel(tr("Название ПО:"));
  _styleLabel = new QLabel(tr("Внешний стиль:"));
  _textEdit   = new QLineEdit();
  _styleCombo = new QComboBox();
  _acceptButton = new QPushButton();

  // Установка внешнего вида приложения
  int style = QString(appsetup.getApplicationParam(
                        QString("Main"),
                        QString("/style"))
                      ).toInt(&ok, 10);

  // FIXME: Эти функции дергают функции записи в файл с настройками.
  // Поэтому createConnectors идет после них.
  _styleCombo->addItem("PlastiqueStyle");
  _styleCombo->addItem("WindowsXPStyle");
  _styleCombo->addItem("WindowsStyle");
  _styleCombo->addItem("CDEStyle");
  _styleCombo->addItem("MotifStyle");

  _acceptButton->setText("Применить");

  createConnectors();

  _styleCombo->setCurrentIndex(style);

  // Установка элементов на layout
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(_textLabel,  0, 0);
  mainLayout->addWidget(_textEdit,   0, 1);
  mainLayout->addWidget(_styleLabel, 1, 0);
  mainLayout->addWidget(_styleCombo, 1, 1);
  mainLayout->addWidget(_styleCombo, 5, 0);
  mainLayout->addWidget(_acceptButton, 7, 0);

  mainLayout->setContentsMargins(1,1,1,1);

  mainLayout->addWidget(ModulesManager::instance().getSettingPage(),
                        6, 0, 1, 2);

  // Установка выравнивания элементов по верхней границе
  mainLayout->setAlignment( Qt::AlignTop );
  // Установка лайаута на форму
  setLayout( mainLayout );

  // Установка названия программы
  _textEdit->setText( QString( appsetup.getApplicationParam( QString("Main"),
                                                 QString("/text"))));

}

/*
 * Функция создания коннекторов
 */
void OptionsPage::createConnectors() {
  QObject::connect(_styleCombo, SIGNAL(currentIndexChanged(int)),
                   this, SLOT(styleComboBoxChanged(int)) );
  QObject::connect(_acceptButton, SIGNAL(clicked()),
                   this, SLOT(acceptButton_onClicked()));
}

/*
 * Изменение текстового поля
 */
void OptionsPage::acceptButton_onClicked() {
  AppSetupApi  appsetup;
//  CveGui::data().mainwindow()->setWindowTitle(text);
  appsetup.setApplicationParam(QString("Main"), QString("/text"),
                               _textEdit->text() );
}

/*
 * Изменение стиля
 */
void OptionsPage::styleComboBoxChanged( int index ) {

  bool ok;
  AppSetupApi  appsetup;

  appsetup.checkApplicationParam(QString("Main"),
                                 QString("/style"),
                                 QString("%1").arg(QPLASTIQUESTYLE) );

  appsetup.setApplicationParam( QString("Main"),
                                QString("/style"),
                                QString("%1").arg(index));


 // Установка внешнего вида приложения
  int style = QString(
       appsetup.getApplicationParam( QString("Main"),
                                     QString("/style"))).toInt( &ok, 10 ) ;

  if ( style == QPLASTIQUESTYLE ) {
    QApplication::setStyle( QStyleFactory::create("Fusion") );
  }

  if ( style == QWINDOWSXPSTYLE ) {
    QApplication::setStyle( QStyleFactory::create("windowsxp") );
  }

  if ( style == QWINDOWSSTYLE ) {
    QApplication::setStyle( QStyleFactory::create("windows") );
  }

  if ( style == QCDESTYLE ) {
    QApplication::setStyle( QStyleFactory::create("Fusion") );
  }

  if ( style == QMOTIFSTYLE ) {
    QApplication::setStyle( QStyleFactory::create("macintosh") );
  }

}

