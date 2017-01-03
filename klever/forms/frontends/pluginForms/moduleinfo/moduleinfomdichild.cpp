#include "moduleinfomdichild.h"
#include <frameWork/managers.h>
#include <library/setupApi/app.h>

ModuleInfoMdiChild::ModuleInfoMdiChild() {

  /* Инициализация сетки расположения графических компонентов */
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  grid->setContentsMargins(1,1,1,1);
//  grid->addWidget(
//        Core::ModulesManager::instance().getMainWindow()
//        );

  /* Добавление сетки на слой виджета */
  setLayout(grid);

  setWindowTitle("Редактор скриптов");

  setMinimumSize(605,400);

  setContentsMargins(1,1,1,1);
//  setWindowIcon( /*CveManager::instance().scriptEditorWidget()->windowIcon()*/ );

}

ModuleInfoMdiChild::~ModuleInfoMdiChild() {
}

/*
 * Закрытие окна
 */
void ModuleInfoMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal( false );
}

/*
 * Сворачивание окна
 */
void ModuleInfoMdiChild::resizeEvent( QCloseEvent *event ) {
Q_UNUSED(event);
}

void ModuleInfoMdiChild::changeEvent(QEvent *event){
  if ( event->type() == QEvent::WindowStateChange ){
    if ( parentWidget()->windowState() == Qt::WindowMinimized ) {
//      emit setVisibleSignal(false);
//        QMetaObject::invokeMethod(parentWidget(), "setVisible", Qt::QueuedConnection, Q_ARG(bool, false) );
    }
  }
}



