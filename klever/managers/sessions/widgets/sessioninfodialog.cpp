#include "sessioninfodialog.h"

#include "sessionstable.h"

using namespace SessionViewNamespace;

SessionInfoDialog::SessionInfoDialog(QDialog *parent) : QDialog(parent)
{
  // Установка флагов для диалогового окна
  setWindowFlags( Qt::Window
                  | Qt::MSWindowsFixedSizeDialogHint
                  | Qt::WindowCloseButtonHint);

  setWindowTitle(tr("Информация сессии ..."));
  // Инициализация сетки расположения графических компонентов
  _infoGridLayout.setSizeConstraint(QLayout::SetDefaultConstraint);
  _textInfoEdit = new QTextEdit;
  _infoGridLayout.addWidget(_textInfoEdit,    0, 0);
  setLayout(&_infoGridLayout);
}

void SessionInfoDialog::setInformation(QString txt)
{
  _textInfoEdit->setText(txt);
}


