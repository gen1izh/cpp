#ifndef CHOOSESERIALNUMBERDIALOG_H
#define CHOOSESERIALNUMBERDIALOG_H

#include <QDialog>

namespace Ui {
class chooseSerialNumberDialog;
}

class chooseSerialNumberDialog : public QDialog
{
  Q_OBJECT

public:
  explicit chooseSerialNumberDialog(QWidget *parent = 0);
  ~chooseSerialNumberDialog();

  /*!
   * \brief Возвращает серийный номер
   * \return
   */
  QString getSerialNumber();

  /*!
   * \brief Устанавливает серийный номер
   * \return
   */
  void setSerialNumber(QString sn);

private:
  Ui::chooseSerialNumberDialog *ui;
};

#endif // CHOOSESERIALNUMBERDIALOG_H
