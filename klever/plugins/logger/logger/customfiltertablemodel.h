#ifndef CUSTOMFILTERTABLEMODEL_H
#define CUSTOMFILTERTABLEMODEL_H

#include "loggerdata.h"

/*******************************************************************************
 *                       Модель источников событий.
 *  Необходима для создания таблицы с перечислением всех источников событий,
 *  которые присутствуют в текущей выбранной таблице журнала сообщений.
 *
 *******************************************************************************/

/*!
 *  \brief  Модель источников событий
 *  \details Необходима для создания таблицы с перечислением всех источников
 *           событий, которые присутствуют в текущей выбранной таблице
 *           журнала сообщений.
 */
class CustomFilterTableModel : public QAbstractTableModel {
    Q_OBJECT

  /*!
   *  \brief Переменная для установки количества строк.
   */
  int   _mRowCount;
  /*!
   *  \brief Установка количества.
   */
  void  setRowCount( int count );

  public:

  /*!
   *  \brief Конструктор класса
   */
    explicit CustomFilterTableModel( QObject *parent = 0 );

  /*!
   *  \brief Возвращает данные хранящиеся под role.
   */
    QVariant data( const QModelIndex &index, int role ) const;

  /*!
   *  \brief Sets the role data for the item at index to value.
   */
    bool setData( const QModelIndex &index, const QVariant &value, int role );

  /*!
   *  \brief Настройка строки заголовка таблицы источников
   *         сообщений окна фильтрации по источнику.
   */
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;

  /*!
   *  \brief Возвращает количество колонок.
   */
    int columnCount( const QModelIndex &parent ) const;

  /*!
   *  \brief Возвращает количество строк
   */
    int rowCount( const QModelIndex &parent ) const;

  /*!
   *  \brief Returns the item flags for the given index.
   *  \details The base class implementation returns a combination
   *           of flags that enables the item (ItemIsEnabled)
   *           and allows it to be selected (ItemIsSelectable).
   */
    Qt::ItemFlags flags( const QModelIndex &index ) const;

  /*!
   *  \brief Карта источников событий.
   */
    MessagesSourcesMap *filter;

  /*!
   *  \brief Переустановка количества строк в таблице.
   */
    void update();

  public slots:

  /*!
   *  \brief Пометить как выбранные все источники событий.
   */
    void selectAll();

  /*!
   *  \brief Пометить как не выбранные все источники событий.
   */
    void deselectAll();
};

#endif // CUSTOMFILTERTABLEMODEL_H
