#ifndef SESSION_INFO_DIALOG_H
#define SESSION_INFO_DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>

class SessionInfoDialog : public QDialog
{
    Q_OBJECT

    QTextEdit *_textInfoEdit;

    QGridLayout _infoGridLayout;

  public:
    explicit SessionInfoDialog(QDialog *parent = 0);

  signals:
  public slots:
   void setInformation(QString txt);
};

#endif // SESSION_INFO_DIALOG_H
