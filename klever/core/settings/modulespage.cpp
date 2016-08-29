#include "modulespage.h"

#include <QListWidgetItem>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QStackedWidget>
#include <QTableWidget>
#include <QToolBox>
#include <QVariant>

/* Глобальные данные */
#include <frameWork/cve.h>
#include <frameWork/cveManager.h>
#include <library/emptypage/emptypage.h>

ModulesPage::ModulesPage(QWidget *parent)
    : QWidget(parent) {

  QVBoxLayout *mainLayout = new QVBoxLayout;
  QToolBox    *tb = new QToolBox();

  if (CveManager::instance().boot()->hasRightUser(CAN_SEE_MODULES_SETTINGS)) {
    if (ModulesManager::instance().modules().isEmpty()) {
      EmptyPage *setting = new EmptyPage(NULL,tr("Страница модулей пуста"));
      mainLayout->addWidget(setting);
      setLayout(mainLayout);
      return;
    }


    QHashIterator<QString,QList<ModulesQueueItem> >  i(
          ModulesManager::instance().modules());
    while (i.hasNext()) {
      i.next();

      for ( int j = 0; j < i.value().size(); j++ ) {
        if ( i.value().at(j).i->getSettingsWidget() == 0) {
          continue;
        }

        tb->addItem(  i.value().at(j).i->getSettingsWidget(),
                      i.value().at(j).i->getModuleIcon(),
                      QString( "%1. %2." )
                      .arg( i.value().at(j).i->getModuleName() )
                      .arg( i.value().at(j).i->getModuleObjName() ) );
      }
    }
  }

  mainLayout->addWidget(tb);
  setLayout(mainLayout);
}

