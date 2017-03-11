#include "texteditormdichild.h"
#include <frameWork/plugins.h>
#include "../../plug.h"

using namespace plug;


TextEditorMdiChild::TextEditorMdiChild() {
  QGridLayout *grid = new QGridLayout();
  grid->setSizeConstraint( QLayout::SetDefaultConstraint );

  QWidget *wgt = getManagerWidget_FromWAPair(tr("texteditor"),
                                             tr("(PM)TextEditor"));

  grid->addWidget(wgt);
  grid->setContentsMargins(1,1,1,1);
  this->setContentsMargins(1,1,1,1);
  setLayout(grid);
  setWindowTitle(wgt->windowTitle());
  setWindowIcon(wgt->windowIcon());
  setMinimumSize(1000, 550);

}

TextEditorMdiChild::~TextEditorMdiChild() {
}


void TextEditorMdiChild::closeEvent( QCloseEvent *event ) {
  event->ignore();
  emit setVisibleSignal(false);
}

