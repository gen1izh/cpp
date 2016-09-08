#include "sessionmanagersettings.h"
#include "sessionmanager.h"
#include <frameWork/cveManager.h>
#include "widgets/sessionstable.h"

using namespace SessionViewNamespace;

SessionManagerSettings::SessionManagerSettings(QWidget *parent) : QWidget(parent)
{

  _roleNameLabel = new QLabel(tr("Название роли:"));
  _rightsLabel   = new QLabel(tr("Права доступа:"));

  _lockAll = new QCheckBox();
  _lockAll->setText(tr("Заблокировать"));

  _roleNameCombo = new QComboBox();

  _roleNameCombo->addItem(Developer);
  _roleNameCombo->addItem(Operator);
//  _roleNameCombo->addItem(Accepter)/*;*/

  _acceptButton  = new QPushButton();

  _acceptButton->setText("Применить");

  _rightsList    = new QListView();

  _rightsListModel = new RightsListModel();
  _rightsList->setModel(_rightsListModel);

  createConnectors();

  initParam();

  // Установка элементов на layout
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(_roleNameLabel, 0, 0, 1, 2);
  mainLayout->addWidget(_roleNameCombo, 1, 0, 1, 2);
  mainLayout->addWidget(_rightsLabel,   2, 0, 1, 2);
  mainLayout->addWidget(_rightsList,    3, 0, 1, 2);
  mainLayout->addWidget(_acceptButton,  4, 1, 1, 1);
  mainLayout->addWidget(_lockAll,       4, 0, 1, 1);

  mainLayout->setContentsMargins(1,1,1,1);

  _rightsLabel->setAlignment(Qt::AlignTop);

  // Установка выравнивания элементов по верхней границе
  mainLayout->setAlignment(Qt::AlignTop);
  // Установка лайаута на форму
  setLayout(mainLayout);

}

/*
 * Инициализация параметров
 */
void SessionManagerSettings::initParam() {
  AppSetupApi                       appsetup;
  bool                              ok;

  appsetup.checkApplicationParam(QString("Session"), QString("locked"), QString("0"));
  bool locked = static_cast<bool>(appsetup.getApplicationParam(QString("Session"),
                                                               QString("locked")).toInt(&ok,10));

 _lockAll->setEnabled(!locked);

 if (locked) {
   _acceptButton->setEnabled(false);
   _roleNameCombo->setEnabled(false);
   _rightsList->setEnabled(false);
   _lockAll->setEnabled(false);
 }

 emit _roleNameCombo->currentIndexChanged(_roleNameCombo->currentText());

}

/*
 * Создать коннекторы
 */
void SessionManagerSettings::createConnectors() {
  connect(_acceptButton, SIGNAL(clicked()), this, SLOT(acceptButton()));

  connect(_roleNameCombo, SIGNAL(currentIndexChanged(const QString &)),
          _rightsListModel, SLOT(setCurrentRole(const QString &)));

  connect(_roleNameCombo, SIGNAL(currentIndexChanged(const QString &)),
          this, SLOT(setCurrentRole(const QString &)));
}

/*
 *
 */
void SessionManagerSettings::acceptButton() {
  AppSetupApi         appsetup;

  if (_lockAll->isChecked()) {
    AppSetupApi  appsetup;
    appsetup.setApplicationParam(QString("Session"),
                                 QString("locked"),
                                 QString("1"));
    _roleNameCombo->setEnabled(false);
    _rightsList->setEnabled(false);
    _lockAll->setEnabled(false);
  }

  QHashIterator<QString, QHash<int, QPair<bool,QString> > >
      j(Core::CveManager::instance().boot()->rights());
  while (j.hasNext()) {
    j.next();

    QString txt = j.key();
    quint16 unic = qChecksum(txt.toStdString().c_str(),txt.size());

    QHashIterator<int, QPair<bool,QString> >
        i(j.value());
    while (i.hasNext()) {
      i.next();
      appsetup.setApplicationParam(QString("Session"),
                                   QString("%1_%2").arg(i.value().second).arg(unic),
                                   QString("%1").arg(i.value().first));
    }
  }

  _acceptButton->setEnabled(false);
}

/*
 *
 */
void SessionManagerSettings::setCurrentRole(const QString &text) {
  Q_UNUSED(text)
    _acceptButton->setEnabled(true);
}
