#include "moduleinfomdichild.h"
#include <frameWork/managers.h>
#include <library/setupApi/app.h>

PluginInfoMdiChild::PluginInfoMdiChild() {

  // Инициализация сетки расположения графических компонентов
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

PluginInfoMdiChild::~PluginInfoMdiChild() {
}

/*
 * Закрытие окна
 */
void PluginInfoMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal( false );
}

/*
 * Сворачивание окна
 */
void PluginInfoMdiChild::resizeEvent( QCloseEvent *event ) {
Q_UNUSED(event);
}

void PluginInfoMdiChild::changeEvent(QEvent *event){
  if ( event->type() == QEvent::WindowStateChange ){
    if ( parentWidget()->windowState() == Qt::WindowMinimized ) {
//      emit setVisibleSignal(false);
//        QMetaObject::invokeMethod(parentWidget(), "setVisible", Qt::QueuedConnection, Q_ARG(bool, false) );
    }
  }
}



