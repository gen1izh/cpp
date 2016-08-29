#ifndef OPTIME_SETTINGS_H
#define OPTIME_SETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class OptimeSettings : public QWidget
{
  Q_OBJECT

  void createConnectors();

  /*!
   * \brief Очистить время наработки КПА
   */
  QPushButton *_clearCveOperationTimeButton;

  /*!
   * \brief Очистить время наработки изделия
   */
  QPushButton *_clearProductOperationTimeButton;

  /*!
   * \brief Время наработки КПА
   */
  QLineEdit *_cveOperationTimeEdit;

  /*!
   * \brief Время наработки изделия
   */
  QLineEdit *_productOperationTimeEdit;

  /*!
   * \brief Время наработки КПА
   */
  QLabel *_cveOperationTimeLabel;

  /*!
   * \brief Время наработки изделия
   */
  QLabel *_productOperationTimeLabel;

public:
  explicit OptimeSettings(QWidget *parent = 0);
  ~OptimeSettings();

  void setOperationTimes(QString cve, QString product) {
    _cveOperationTimeEdit->setText(cve);
    _productOperationTimeEdit->setText(product);
  }

public slots:
  /*!
   * \brief Очистка, обнуление времени наработки для КПА
   */
  void clearCveOperationTime();
  /*!
   * \brief Очистка, обнуление времени наработки для изделия
   */
  void clearProductOperationTime();

signals:

  /*!
   * \brief Сигнал очисткивремени наработки КПА
   */
  void clearCveOperationTimeSignal();

  /*!
   * \brief Сигнал очисткивремени наработки изделия
   */
  void clearProductOperationTimeSignal();

};

#endif // OPTIME_SETTINGS_H

