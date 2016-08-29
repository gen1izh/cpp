#ifndef EMPTYPAGE_H
#define EMPTYPAGE_H

#include <QWidget>

/*!
 * \brief Пустая страница
 */
class EmptyPage : public QWidget {
  public:
    /*!
     * \brief Конструктор класса пустой страницы
     * \param[in] parent - указатель на родительский класс
     * \param[in] txt - текст на пустой странице
     */
    EmptyPage(QWidget *parent = 0, QString txt= QString());
};

#endif // EMPTYPAGE_H
