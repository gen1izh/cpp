#include "processdialog.h"

/*
 * Создание коннекторов
 */
void ProcessDialog::createConnectors()
{
  connect(&_cancelButton, SIGNAL(clicked()),this, SLOT(finish()) );
}

/*
 * Отображение диалогового окна при выполнении длительного действия
 */
void ProcessDialog::setDialog(QString text) {

  _cancelButton.setText("Отмена");
  _processLabel.setText(text);

  _processBar.setValue(1);
  _processBar.setMaximum(0);

  // Установка флагов для диалогового окна
  _dialog.setWindowFlags( Qt::Window
                        | Qt::MSWindowsFixedSizeDialogHint
                        | Qt::WindowCloseButtonHint);

  _dialog.setWindowTitle("Ожидайте...");

  createConnectors();

  _processLayout.addWidget(&_processLabel);
  _processLayout.addWidget(&_processBar);
  _processLayout.addWidget(&_cancelButton);

  _dialog.setLayout(&_processLayout);
}

/*
 * Выдача сигнала завершения диалогового окна
 */
void ProcessDialog::finish()
{
  _dialog.hide();
  emit finished();
}

/*
 * Выдача сигнала для открытия диалогового окна
 */
void ProcessDialog::start()
{
  _dialog.show();
  emit started();
}


