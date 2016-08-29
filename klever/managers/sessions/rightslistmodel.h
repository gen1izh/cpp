#ifndef RIGTHSLISTMODEL_H
#define RIGTHSLISTMODEL_H

#include <QWidget>
#include <QStringListModel>

#include <library/setupApi/app.h>


/*!
 * \brief Модель списка прав доступа
 */
class RightsListModel : public QStringListModel
{
  Q_OBJECT


  /*!
   * \brief Список названий модулей
   */
  QStringList _rightsStringList;

  QString     _role;

  public:

    /*!
     * \brief Конструктор модели списка модулей
     * \param[in] parent указатель на класс родителя
     */
    RightsListModel(QWidget *parent = 0);

    /*!
     * \brief Обработчик данных
     * \param[in] index модельный индекс списка
     * \param[in] role роль
     * \return данные
     */
    QVariant data(const QModelIndex &index, int role) const;

    /*!
     * \brief Флаги
     * \param[in] index модельный индекс списка
     * \return
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*!
     * \brief Установка данных в модель
     * \param[in] index модельный индекс списка
     * \param[in] value значение
     * \param[in] role роль
     * \return признак уставки данных
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role);

public slots:
    void setCurrentRole(const QString &text) {
      _role = text;
      emit dataChanged(QModelIndex(),QModelIndex());
    }


};

#endif // RIGTHSLISTMODEL_H
