#ifndef RICHTEXTDELEGATE_H
#define RICHTEXTDELEGATE_H

#include "richtextlineedit.h"
#include <QItemDelegate>
#include <QPixmapCache>
#include <QPainter>
#include <QCheckBox>
#include <QLabel>


/******************************************************************************
 *   Класс делегата для первой колонки таблицы тестовых последовательностей.
 *   Для того чтобы первая колонка была как checkbox.
 ******************************************************************************/

/*!
 *  Класс делегат 1-ой колонки таблицы тестовой последовательности
 */
class RichTextDelegate : public QItemDelegate {

    Q_OBJECT

  public:

    /*!
     * \brief Конструктор делегата
     * \param parent
     */
    explicit RichTextDelegate( QObject *parent = 0 );

    /*!
     * Деструктор checkbox и label
     */
    ~RichTextDelegate() {
      delete checkbox;
      delete label;
    }

    /*!
     * \brief Рисует элемент с модельным индексом.
     *        Редко переопределяется для простых данных - текста, дат, чисел.
     * \param painter
     * \param option
     * \param index
     */
    void paint( QPainter *painter, const QStyleOptionViewItem &option,
                const QModelIndex &index ) const;
    /*!
     * \brief Переопределение длины текста без html тегов
     * \param option
     * \param index
     * \return
     */
    QSize sizeHint( const QStyleOptionViewItem &option,
                    const QModelIndex &index ) const;

    /*!
     * \brief Создание редактора для элемента с переданным модельным индексом
     * \param parent
     * \param option
     * \param index
     * \return
     */
    QWidget *createEditor( QWidget *parent,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index ) const;

    /*!
     * \brief Установка данных для модели
     * \param editor
     * \param index
     */
    void setEditorData( QWidget *editor,
                        const QModelIndex &index ) const;

    /*!
     * \brief Установка данных в модель после завершения операции редактирования
     * \param editor
     * \param model
     * \param index
     */
    void setModelData( QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index ) const;

  private slots:

    /*!
     * \brief Генерация сигнала успешного завершения редактора
     */
    void closeAndCommitEditor();

    /*!
     * \brief textChangedEditor
     */
    void textChangedEditor();

  private:

    /*!
     * \brief Рисование виджетов
     * \param painter
     * \param rect
     * \param cacheKey
     * \param widget
     */
    void paintWidget( QPainter *painter, const QRect &rect,
                      const QString &cacheKey, QWidget *widget ) const;

    /*!
     * \brief Checkbox для выбора тест-кейса
     */
    QCheckBox     *checkbox;

    /*!
     * \brief Метка для текста
     */
    QLabel        *label;

    /*!
     * \brief TODO: Написать что за документ
     */
    mutable QTextDocument  document;

  signals:
    void changedData();
};

#endif // RICHTEXTDELEGATE_H
