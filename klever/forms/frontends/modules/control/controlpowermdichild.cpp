#include "controlpowermdichild.h"

#include <frameWork/cve.h>


ControlMdiChild::ControlMdiChild() {

  /* Инициализация сетки расположения графических компонентов */
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );


  // ЗАПОЛНЕНИЕ MDI Формы виджетами  модулей


  /*TODO: Делать проверки на пустые объекты !!! */

//  QHashIterator<QString,QList<ModulesQueueItem> >  i(CveManager::instance().modulesManager()->modules());
//  while (i.hasNext()) {
//    i.next();

//    if ( i.value().at(0).i->getModuleSysName() == "power" ) {

//      if ( (i.value().size() ) > 0 /* TODO: если в списке хотя бы 1 элемент */ ) {
//        grid->addWidget( i.value().at(0).i->
//                         getWidgetActionList()["(Power)KpaDualChannelsIndicatorsWidget"].first, 0, 0 );
//      }

//      if ( (i.value().size() ) > 1 /* TODO: если в списке хотя бы 1 элемент */ ) {
//        grid->addWidget( i.value().at(1).i->
//                         getWidgetActionList()["(Power)KpaChannelsIndicatorsOnFormWidget"].first, 1, 0 );
//      }
//    }

//    if ( i.value().at(0).i->getModuleSysName() == "ftdi_bitbang" ) {
//      if ( (i.value().size()) > 0 /* TODO: если в списке хотя бы 1 элемент */ ) {
//        grid->addWidget( i.value().at(0).i->
//                         getWidgetActionList()["(Ftdi)BootModeWidget"].first, 2, 0 );
//      }
//    }

//    if ( i.value().at(0).i->getModuleSysName() == "pxi6528" ) {
//      if ( (i.value().size() ) > 0 /* TODO: если в списке хотя бы 1 элемент */ ) {
//        grid->addWidget( i.value().at(0).i->
//                         getWidgetActionList()["(Pxi6528)ControlCommandsWidget"].first, 0, 2, 3, 1, Qt::AlignTop );
//      }
//    }

//  }

  setLayout( grid );
  setWindowTitle( "Управление" );
  setWindowIcon( QIcon(":/control/img/control.png") );

}

ControlMdiChild::~ControlMdiChild() {
}

/*
 * Закрытие окна
 */
void ControlMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal( false );
}
