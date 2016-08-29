#ifndef MODULESLISTMODEL_H
#define MODULESLISTMODEL_H

#include <QWidget>
#include <QStringListModel>

#include <library/setupApi/app.h>


/*!
 * \brief Модель списка модулей
 */
class ModulesListModel : public QStringListModel
{
  Q_OBJECT

  /*!
   * \brief Признак проверки, что модуль выбран
   */
  QHash <QString, bool> _isChecked;

  /*!
   * \brief Список названий модулей
   */
  QStringList _modulesStringList;



  public:

    /*!
     * \brief Конструктор модели списка модулей
     * \param[in] parent указатель на класс родителя
     */
    ModulesListModel(QWidget *parent = 0);

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

    /*!
     *  Список модулей загрузившихся с багом
     */
    QStringList bugModules;
};

#endif // MODULESLISTMODEL_H
