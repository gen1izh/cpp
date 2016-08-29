#ifndef RICHTEXTLINEEDIT_H
#define RICHTEXTLINEEDIT_H

/******************************************************************************
 *                   Переопределенный класс QTextEdit для
 *                 обеспечения редактирования поля делегата
 ******************************************************************************/

//#include "..\data.h"

#include <QKeyEvent>

#include <QTextEdit>


/*!
 * \brief Текстовое поле
 */
class RichTextLineEdit : public QTextEdit {
   Q_OBJECT

 public:

  /*!
    * \brief Конструктор элемента RichText текстового поля
    * \param parent
    */
   explicit RichTextLineEdit(QWidget *parent=0);

  /*!
    * \brief Переопределение размера текста
    * \return
    */
   QSize sizeHint() const;

   /*!
    * \brief Возвращает минимальный размер текста
    * \return
    */
   QSize minimumSizeHint() const;

 signals:

   /*!
    * \brief Сигнал нажатия на клавишу
    */
   void returnPressed();

 protected:

   /*!
    * \brief Обработчик нажатия на клавиш
    * \param event
    */
   void keyPressEvent(QKeyEvent *event);

};



#endif // RICHTEXTLINEEDIT_H
