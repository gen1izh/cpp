#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include <QVariant>
#include <QReadWriteLock>
#include <QString>

/*!
 * \brief Определение параметра для обмена данными между модулями и менеджерами.
 */
class Parameter : public QObject
{
  Q_OBJECT

  QVariant                _value;
  mutable QReadWriteLock  _valueLock;

public:
  explicit Parameter(const QString &name, QObject *parent = 0);

  QString getName() const { return objectName(); }

  virtual QVariant getValue() const;

  template <typename T>
  T getValue() const { return getValue().value<T>(); }

signals:
  void valueChanged(const QVariant &newValue);

public slots:
  virtual void setValue(const QVariant &value);


};

#endif // PARAMETER_H
