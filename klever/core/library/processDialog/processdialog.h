#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QProgressBar>
#include <QString>

class ProcessDialog : public QObject
{
  Q_OBJECT

  QWidget      _dialog;
  QPushButton  _cancelButton;
  QLabel       _processLabel;
  QGridLayout  _processLayout;
  QProgressBar _processBar;

  void createConnectors();

public:
  ProcessDialog(){}
  ~ProcessDialog(){}

  /*!
   * \brief Установка окна процесса
   * \param[in] text - текст процесса
   */
  void setDialog(QString text);

public slots:

  /*!
   * \brief Выдача сигнала завершения диалогового окна
   */
  void finish();

  /*!
   * \brief Выдача сигнала для открытия диалогового окна
   */
  void start();

signals:

  /*!
   * \brief Сигнал завершения процесса
   */
  void finished();

  /*!
   * \brief Сигнал начала процесса
   */
  void started();
};

#endif // PROCESSDIALOG_H
