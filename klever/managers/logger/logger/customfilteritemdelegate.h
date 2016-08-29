#ifndef CUSTOMFILTERITEMDELEGATE_H
#define CUSTOMFILTERITEMDELEGATE_H


#include "loggerdata.h"

/*******************************************************************************
 *                   Делегат для модели источников событий.
 *******************************************************************************/

/*!
 *  \brief  Делегат для модели источников событий.
 */
class CustomFilterItemDelegate : public QItemDelegate {
    Q_OBJECT

  protected:

  /*!
   *  \brief Прорисовка источников фильтрации
   */
    void paint(       QPainter *painter,
                const QStyleOptionViewItem &option,
                const QModelIndex &index
               ) const;

  /*!
   *  \brief Событие редактирования данных.
   */
    bool editorEvent(       QEvent *event,
                            QAbstractItemModel *model,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index );

  public:

  /*!
   *  \brief Конструктор класса.
   */
    CustomFilterItemDelegate( QObject *parent = 0 );

    /*!
     *  \brief Прямоугольники checkBox`ов.
     */
    const QRect CheckBoxRect(
                const QStyleOptionViewItem &viewItemStyleOptions ) const;

  /*!
   *  \brief Создание редактора.
   */
    QWidget *createEditor(        QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index ) const;

  /*!
   *  \brief Установка данных редактора.
   */
    void setEditorData(       QWidget *editor,
                        const QModelIndex &index ) const;

    /*!
     *  \brief Установка модели данных.
     */
    void setModelData(
                                QWidget *editor,
                                QAbstractItemModel *model,
                          const QModelIndex &index
                        ) const;

    /*!
     *  \brief Обновить редактор.
     */
    void updateEditorGeometry(
                              QWidget *editor,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index
      ) const;


};

#endif // CUSTOMFILTERITEMDELEGATE_H
