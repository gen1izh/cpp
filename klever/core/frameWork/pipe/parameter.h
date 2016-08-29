#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include <QVariant>
#include <QReadWriteLock>

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

  virtual void setValue(const QVariant &value);

  template <typename T>
  T getValue() const { return getValue().value<T>(); }

  template <typename T>
  void setValue(T value) {
    QVariant var_value;
    var_value.setValue(value);
    setValue(var_value);
  }

signals:
  void valueChanged(const QVariant &newValue);

};

#endif // PARAMETER_H
