#ifndef CUSTOMFILTERDIALOG_H
#define CUSTOMFILTERDIALOG_H

#include "loggerdata.h"
#include "customfiltertablemodel.h"
#include "customfilteritemdelegate.h"

/*******************************************************************************
 *                   Диалоговое окно фильтрации сообщений.
 *
 *
 *
 *******************************************************************************/


/*!
 *  \brief Класс диалогового окна фильтрации сообщений журнала.
 *  \details
 */
class CustomFilterDialog : public QDialog {
    Q_OBJECT

  /*!
   *  \brief Модуль источников событий.
   */
  CustomFilterTableModel   *_model;

  /*!
   *  \brief Делегат на модель источников собыйтий.
   */
  CustomFilterItemDelegate *_itemDelegate;

  public:

  /*!
   *  \brief Конструктор класса
   */
    explicit CustomFilterDialog(QWidget *parent = 0);

  /*!
   *  \brief Деструктор класса
   */
    ~CustomFilterDialog();

  /*!
   *  \brief Обновления карты источников событий.
   */
    bool setSourcesMap(MessagesSourcesMap *filter);

  /*!
   *  \brief Выделить все источники.
   */
    QPushButton    *selectAllButton;

    /*!
     *  \brief Снять все источники.
     */
    QPushButton    *deselectAllButton;

    /*!
     *  \brief Тип сообщения.
     */
    QComboBox      *msgTypeComboBox;

    /*!
     *  \brief Начать фильтрацию.
     */
    QPushButton    *okButton;

    /*!
     *  \brief Закрыть окно фильтрации.
     */
    QPushButton    *closeButton;

    /*!
     *  \brief Таблица представления данных.
     */
    QTableView     *tableView;

    /*!
     *  \brief Условие фильтрации по дате.
     */
    QCheckBox      *byDateFilterEnableCheckBox;

    /*!
     *  \brief Начальная граница даты
     */
    QLabel         *startDatePointLabel;

    /*!
     *  \brief Конечная граница даты.
     */
    QLabel         *stopDatePointLabel;

    /*!
     *  \brief Начальная граница даты
     */
    QDateTimeEdit  *startDatePointLineEdit;

    /*!
     *  \brief Конечная граница даты.
     */
    QDateTimeEdit  *stopDatePointLineEdit;


    QGroupBox      *gbx2;

};





#endif // CUSTOMFILTERDIALOG_H
