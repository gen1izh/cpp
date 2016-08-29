#ifndef RENAME_TEST_DIALOG_H
#define RENAME_TEST_DIALOG_H

#include <QDialog>

namespace Ui {
class RenameTestDialog;
}

class RenameTestDialog : public QDialog
{
  Q_OBJECT

    void createConnectors();

    /*!
     * \brief Имя тестовой последовательности
     */
    QString _text;

  public:
    explicit RenameTestDialog(QWidget *parent = 0);
    ~RenameTestDialog();

    /*!
     * \brief Возвращет название тестовой последовательности
     * \return
     */
    QString getText() {
      return _text;
    }

  private slots:
    void on_testNameEdit_textChanged(QString txt);

  private:
    Ui::RenameTestDialog *ui;
};

#endif // RENAME_TEST_DIALOG_H
