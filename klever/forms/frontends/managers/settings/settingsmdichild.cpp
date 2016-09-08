#include "settingsmdichild.h"
#include <unistd.h>
#include <frameWork/cveManager.h>

SettingsMdiChild::SettingsMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );
  grid->setContentsMargins(1,1,1,1);
  grid->addWidget(Core::Base::instance().setting());  // Добавляем виджет настроек
  setContentsMargins(1,1,1,1);
  setLayout( grid );
  setMinimumSize(800,500);
  setWindowTitle( "Настройки приложения" );
  setWindowIcon( Core::Base::instance().setting()->windowIcon() );
}

void SettingsMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}


