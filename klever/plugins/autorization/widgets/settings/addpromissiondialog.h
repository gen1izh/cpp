#ifndef ADD_PROMISSION_DIALOG_H
#define ADD_PROMISSION_DIALOG_H

#include <QDialog>

namespace Ui {
class AddPromissionDialog;
}

class AddPromissionDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AddPromissionDialog(QWidget *parent = 0);
  ~AddPromissionDialog();

  QString name() const;
  QString signature() const;

private:
  Ui::AddPromissionDialog *ui;
};

#endif // ADD_PROMISSION_DIALOG_H
