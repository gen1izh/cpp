#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>

#include "modulespage.h"
#include "optionsform.h"


/*!
 * \brief Основной класс настроек приложения
 */
class AppSettings : public QWidget {
    Q_OBJECT

  /*!
   * \brief Контент настроек
   */
  QListWidget     *m_contentsWidget;
  /*!
   * \brief Страницы настроек
   */
  QStackedWidget  *m_pagesWidget;

  public:
    /*!
     * \brief Конструктор настроек
     * \param[in] parent - родительский класс
     */
    explicit AppSettings(QWidget *parent = 0);

    /*!
     * \brief Функция создания иконок на менюшку настроек
     */
    void createIcons();

  public slots:
    /*!
     * \brief Функция выбора страницы настроек
     * \param[in] current  - текущая страница настроек
     * \param[in] previous -  предыдущая страница настроек
     */
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);

};
#endif // APPSETTINGS_H
